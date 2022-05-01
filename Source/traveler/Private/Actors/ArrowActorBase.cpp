// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ArrowActorBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Damage/DamageHandlerInterface.h"
#include "GameSystem/MyGameplayStatics.h"

AArrowActorBase::AArrowActorBase()
{
	if (!_primitiveComp)
	{
		_primitiveComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
		check(_primitiveComp);
		SetRootComponent(_primitiveComp);
		_primitiveComp->SetCollisionProfileName(FName("Projectile"));
	}

	if (!_headEffect)
	{
		_headEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Head Effect"));
		check(_headEffect);
		_headEffect->AttachToComponent(_primitiveComp, FAttachmentTransformRules::KeepWorldTransform);
	}

	if (!_headTrailEffect)
	{
		_headTrailEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Head Trail Effect"));
		check(_headTrailEffect);
		_headTrailEffect->AttachToComponent(_primitiveComp, FAttachmentTransformRules::KeepWorldTransform);
		_headTrailEffect->Deactivate();
	}

	if (!_tailTrailEffect)
	{
		_tailTrailEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tail Trail Effect"));
		check(_headEffect);
		_tailTrailEffect->AttachToComponent(_primitiveComp, FAttachmentTransformRules::KeepWorldTransform);
		_tailTrailEffect->Deactivate();
	}

	_timeToDrop = 5.0f;
	_arrowState = EArrowState::EAS_Spawned;
	_gravity = 0.1f;
	_lifeAfterLaunch = 20.0f;
	_lifeAfterHit = 5.0f;
	_basicSpeed = 2000.0f;
	_damage = 5.0f;

	_elapsedTimeFromLaunch = 0.0f;
	_elapsedTimeFromHit = 0.0f;
}

void AArrowActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (_primitiveComp)
	{
		_primitiveComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//OnHit 
		_primitiveComp->OnComponentHit.AddDynamic(this, &AArrowActorBase::VOnHit);
	}
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
			VInActivate();
		}
	}

	if (_arrowState == EArrowState::EAS_Hitted)
	{
		_elapsedTimeFromHit += DeltaTime;

		//inactivate 
		if (_elapsedTimeFromHit > _lifeAfterHit)
		{
			VInActivate();
		}
	}
}

void AArrowActorBase::Launch(float strength)
{
	_arrowState = EArrowState::EAS_Launched;
	_primitiveComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	_tailTrailEffect->Activate();
	_headTrailEffect->Activate();

	VSetVelocity(_launchDirection * _basicSpeed * strength);
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
	_headTrailEffect->Deactivate();
	_tailTrailEffect->Deactivate();
	FDetachmentTransformRules detachRule(EDetachmentRule::KeepWorld,true);
	DetachFromActor(detachRule);
}

void AArrowActorBase::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (_arrowState == EArrowState::EAS_Hitted) return;

	_projectileMovementComp->Velocity = FVector::ZeroVector;
	_arrowState = EArrowState::EAS_Hitted;
	_primitiveComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	_headTrailEffect->Deactivate();
	_tailTrailEffect->Deactivate();

	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity, Hit.ImpactPoint);
	}

	//Todo
	AttachToComponent(OtherComponent, FAttachmentTransformRules::KeepWorldTransform, Hit.BoneName);

	//apply damagge
	UMyGameplayStatics::CauseDamage(OtherActor, _damageData, Hit.ImpactPoint, this, GetInstigator());
}