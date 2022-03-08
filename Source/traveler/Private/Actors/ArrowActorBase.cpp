// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ArrowActorBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AArrowActorBase::AArrowActorBase()
{
	_timeToDrop = 5.0f;
	_arrowState = EArrowState::EAS_Spawned;
	_gravity = 0.1f;
	_lifeAfterLaunch = 20.0f;
	_lifeAfterHit = 5.0f;
	_basicSpeed = 2000.0f;
	_damage = 5.0f;

	_elapsedTimeFromLaunch = 0.0f;
	_elapsedTimeFromHit = 0.0f;

	if(_meshComp)
	{
		_meshComp->SetCollisionProfileName(FName("Projectile"));
	}
}

void AArrowActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (_damageTypeClass)
	{
		_damageType = NewObject<UDamageType>(this, _damageTypeClass);
	}

	if (_meshComp)
	{
		_meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//OnHit 
		_meshComp->OnComponentHit.AddDynamic(this, &AArrowActorBase::VOnHit);
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
			VSetIsActive(false);
		}
	}

	if (_arrowState == EArrowState::EAS_Hitted)
	{
		_elapsedTimeFromHit += DeltaTime;

		//inactivate 
		if (_elapsedTimeFromHit > _lifeAfterHit)
		{
			VSetIsActive(false);
		}
	}
}

void AArrowActorBase::Launch(float strength)
{
	_arrowState = EArrowState::EAS_Launched;
	_meshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

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
	_meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FDetachmentTransformRules detachRule(EDetachmentRule::KeepWorld,true);
	DetachFromActor(detachRule);
	//DetachRootComponentFromParent();
	
}

void AArrowActorBase::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//_projectileMovementComp->Velocity = FVector::ZeroVector;
	_arrowState = EArrowState::EAS_Hitted;
	//_meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity, Hit.ImpactPoint);
	}
	//Todo
	AddActorWorldOffset(GetActorForwardVector() * 30);
	AttachToComponent(OtherComponent, FAttachmentTransformRules::KeepWorldTransform, Hit.BoneName);

	if (OtherActor != GetInstigator())
	{
		UGameplayStatics::ApplyDamage(OtherActor, _damage, GetInstigator()->GetController(), this, _damageTypeClass);
		//UGameplayStatics::apply
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("arrow hitted"));
}