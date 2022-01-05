// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThrowableActor.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AThrowableActor::AThrowableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!_rootSceneComp)
	{
		_rootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComp"));
	}

	if (!_projectileMovementComp)
	{
		// Use this component to drive this projectile's movement.
		_projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
		_projectileMovementComp->SetUpdatedComponent(RootComponent);
		_projectileMovementComp->InitialSpeed = 0.0f;
		_projectileMovementComp->MaxSpeed = 3000.0f;
		_projectileMovementComp->bRotationFollowsVelocity = true;
		_projectileMovementComp->bShouldBounce = false;
		_projectileMovementComp->Bounciness = 0.3f;
		_projectileMovementComp->ProjectileGravityScale = 0.0f;
	}
}

// Called when the game starts or when spawned
void AThrowableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AThrowableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_elapsedTime += DeltaTime;

	if (_elapsedTime > _life)
	{
		VSetIsActive(false);
	}

}

void AThrowableActor::VSetDirection(FVector dir)
{
	_projectileMovementComp->Velocity = dir;
}

void AThrowableActor::VSetSpeed(float speed)
{
	_projectileMovementComp->InitialSpeed = speed;
}

void AThrowableActor::VSetLife(float life)
{
	_life = life;
}

bool AThrowableActor::VIsActive()
{
	return _isActive;
}

void AThrowableActor::VSetIsActive(bool isActive)
{
	if (_isActive == isActive) return;

	_isActive = isActive;

	SetActorTickEnabled(_isActive);
	SetActorHiddenInGame(!_isActive);

	if (!_isActive)
	{
		_elapsedTime = 0.0f;
		OnActorInactivated.ExecuteIfBound(_poolId);
	}
}

int AThrowableActor::VGetPoolId()
{
	return _poolId;
}

void AThrowableActor::VSetPoolId(int poolId)
{
	_poolId = poolId;
}

