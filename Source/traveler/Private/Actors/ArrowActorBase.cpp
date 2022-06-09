// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ArrowActorBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Damage/DamageHandlerInterface.h"
#include "GameSystem/MyGameplayStatics.h"
#include "Data/TagNames.h"


AArrowActorBase::AArrowActorBase()
{
	if (!_primitiveComp)
	{
		_primitiveComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
		check(_primitiveComp);
		SetRootComponent(_primitiveComp);
		_primitiveComp->SetCollisionProfileName(FName("Projectile"));
		_primitiveComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (!_headEffect)
	{
		_headEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Head Effect"));
		check(_headEffect);
		_headEffect->SetupAttachment(_primitiveComp);
	}

	if (!_tailTrailEffect)
	{
		_tailTrailEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tail Trail Effect"));
		check(_tailTrailEffect);
		_tailTrailEffect->SetupAttachment(_primitiveComp);
		_tailTrailEffect->Deactivate();
	}

	_timeToDrop = 5.0f;
	_arrowState = EArrowState::EAS_Spawned;
	_gravity = 0.1f;
	_lifeAfterLaunch = 20.0f;
	_lifeAfterHit = 5.0f;
	_basicSpeed = 2000.0f;

	_elapsedTimeFromLaunch = 0.0f;
	_elapsedTimeFromHit = 0.0f;
	
}

void AArrowActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AArrowActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_arrowState == EArrowState::EAS_Launched)
	{
		_elapsedTimeFromLaunch += DeltaTime;

		//apply gravity
		if (_elapsedTimeFromLaunch > _timeToDrop)
		{
			_projectileMovementComp->ProjectileGravityScale = _gravity;
		}

		//inactivate 
		if(_elapsedTimeFromLaunch > _lifeAfterLaunch)
		{
			VDeactivate();
		}
	}

	if (_arrowState == EArrowState::EAS_Hitted)
	{
		_elapsedTimeFromHit += DeltaTime;

		//inactivate 
		if (_elapsedTimeFromHit > _lifeAfterHit)
		{
			VDeactivate();
		}
	}

	if (GetInstigator())
	{
		CustomTimeDilation = GetInstigator()->CustomTimeDilation;
	}


	//todo: Performance optimization
	if (CustomTimeDilation != 1.0f)
	{
		//_headEffect->SetPaused(false);
		_headEffect->AdvanceSimulation(1, DeltaTime);
		//_headEffect->SetPaused(true);
		//_tailTrailEffect->SetPaused(false);
		_tailTrailEffect->AdvanceSimulation(1, DeltaTime);
		//_tailTrailEffect->SetPaused(true);
	}
}

void AArrowActorBase::SetArrowData(UArrowData* arrowData)
{
	check(_headEffect);
	check(_tailTrailEffect);
	check(arrowData);

	_headEffect->SetAsset(arrowData->Effect_Head);
	_tailTrailEffect->SetAsset(arrowData->Effect_TailTrail);
	_decalActorClass = arrowData->DecalActorClass;

	_damageData = arrowData->DamageData;
}

void AArrowActorBase::Launch(float speedScale)
{
	_arrowState = EArrowState::EAS_Launched;
	_primitiveComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	_tailTrailEffect->Activate();
	VSetVelocity(_launchDirection * _basicSpeed * speedScale);
}

void AArrowActorBase::SetLaunchDirection(FVector dir)
{
	_launchDirection = dir;
}

void AArrowActorBase::VReset()
{
	Super::VReset();

	_arrowState = EArrowState::EAS_None;
	_elapsedTimeFromLaunch = 0.0f;
	_elapsedTimeFromHit = 0.0f;
	_projectileMovementComp->ProjectileGravityScale = 0.0f;
	_primitiveComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	_tailTrailEffect->Deactivate();
	FDetachmentTransformRules detachRule(EDetachmentRule::KeepWorld,true);
	DetachFromActor(detachRule);
	
	_projectileMovementComp->Activate(true);
}

void AArrowActorBase::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (_arrowState == EArrowState::EAS_Hitted) return;

	_arrowState = EArrowState::EAS_Hitted;
	_primitiveComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	_projectileMovementComp->StopMovementImmediately();
	_projectileMovementComp->Activate(false);
	_tailTrailEffect->Deactivate();

	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity, Hit.ImpactPoint);
	}

	if(_decalActorClass && OtherActor && 
		(OtherActor->ActorHasTag(NSTagName::Ground) || OtherActor->ActorHasTag(NSTagName::Wall)))
	{
		FActorSpawnParameters spawnParams;
		FQuat quat = FQuat::FindBetweenVectors(FVector::UpVector, Hit.Normal);
		GetWorld()->SpawnActor<AActor>(_decalActorClass, Hit.ImpactPoint, quat.Rotator(), spawnParams);
	}

	//Todo
	AttachToComponent(OtherComponent, FAttachmentTransformRules::KeepWorldTransform, Hit.BoneName);

	//apply damagge
	UMyGameplayStatics::CauseDamage(OtherActor, _damageData, Hit.ImpactPoint, this, GetInstigator());
}