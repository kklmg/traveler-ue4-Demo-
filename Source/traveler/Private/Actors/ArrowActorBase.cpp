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

	_elapsedTimeFromLaunch = 0.0f;
	_elapsedTimeFromHit = 0.0f;
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
		//OnHit 
		//_meshComp->OnComponentHit.AddDynamic(this, &AArrowActorBase::VOnHit);
		_meshComp->OnComponentBeginOverlap.AddDynamic(this, &AArrowActorBase::VOnOverlapBegin);
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
			DetachRootComponentFromParent(true);
		}
	}
}

void AArrowActorBase::Launch(float strength)
{
	_arrowState = EArrowState::EAS_Launched;

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

	FDetachmentTransformRules detachRule(EDetachmentRule::KeepWorld,true);
	DetachRootComponentFromParent(true);
}

void AArrowActorBase::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		//OtherComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity * 100.0f, Hit.ImpactPoint);
	}
	AttachToComponent(OtherComponent, FAttachmentTransformRules::KeepWorldTransform);

	FTimerHandle WaitHandle;
	float WaitTime = 5;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
	{
		Destroy();

	}), WaitTime, false);

	if (OtherActor != GetInstigator())
	{
		UGameplayStatics::ApplyDamage(OtherActor, _damage, GetInstigator()->GetController(), this, _damageTypeClass);
	}
}

void AArrowActorBase::VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_projectileMovementComp->Velocity = FVector::ZeroVector;
	_arrowState = EArrowState::EAS_Hitted;
	
	AttachToComponent(OverlappedComponent, FAttachmentTransformRules::KeepWorldTransform);

	if (OtherActor != this && OverlappedComponent->IsSimulatingPhysics())
	{
		OverlappedComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity * 100.0f, SweepResult.ImpactPoint);
	}

	APawn* instigator = GetInstigator();

	if (OtherActor != instigator)
	{
		UGameplayStatics::ApplyDamage(OtherActor, _damage, instigator ? GetInstigator()->GetController() : nullptr, this, _damageTypeClass);
	}
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
	{
		
	}
	

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("arrow hitted"));
}



//void AArrowActorBase::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
//	{
//		OtherComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity * 100.0f, Hit.ImpactPoint);
//	}
//
//	APawn* instigator = GetInstigator();
//
//	if (OtherActor != instigator)
//	{
//		UGameplayStatics::ApplyDamage(OtherActor, _damage, instigator ? GetInstigator()->GetController() : nullptr, this, _damageTypeClass);
//	}
//	VSetIsActive(false);
//}
//
//void AArrowActorBase::VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//
//}