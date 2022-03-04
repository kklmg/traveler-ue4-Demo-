// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ProjectileActorBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileActorBase::AProjectileActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//if (!_rootSceneComp)
	//{
	//	_rootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComp"));
	//	SetRootComponent(_rootSceneComp);
	//}

	if (!_meshComp)
	{
		_meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
		_meshComp->AttachToComponent(_rootSceneComp, FAttachmentTransformRules::KeepRelativeTransform);
		RootComponent = _meshComp;
	}

	if (!_projectileMovementComp)
	{
		// Use this component to drive this projectile's movement.
		_projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
		//_projectileMovementComp->SetUpdatedComponent(_rootSceneComp);
		_projectileMovementComp->InitialSpeed = 0.0f;
		_projectileMovementComp->MaxSpeed = 3000.0f;
		_projectileMovementComp->bRotationFollowsVelocity = true;
		_projectileMovementComp->bShouldBounce = false;
		_projectileMovementComp->Bounciness = 0.3f;
		_projectileMovementComp->ProjectileGravityScale = 0.0f;
	}

	_lifeTime = 60.0f;
	_bHasLife = false; 
	_bIgnoreInstigator = true;
}

// Called when the game starts or when spawned
void AProjectileActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (_bIgnoreInstigator && GetInstigator())
	{
		_meshComp->IgnoreActorWhenMoving(GetInstigator(), true);
		GetInstigator()->MoveIgnoreActorAdd(this);
	}
}

// Called every frame
void AProjectileActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isActive == false) return;

	_elapsedLifeTime += DeltaTime;
	if (_bHasLife && _elapsedLifeTime > _lifeTime)
	{
		VSetIsActive(false);
	}
}

void AProjectileActorBase::VSetLife(float life)
{
	_lifeTime = life;
}

bool AProjectileActorBase::VIsActive()
{
	return _isActive;
}

void AProjectileActorBase::VSetIsActive(bool isActive)
{
	if (_isActive == isActive) return;

	_isActive = isActive;

	SetActorTickEnabled(_isActive);
	SetActorHiddenInGame(!_isActive);
	SetActorEnableCollision(_isActive);

	if(_isActive)
	{
		VReset();
		VOnActive();
	}
	else
	{
		VOnInActive();
		
	}
}

void AProjectileActorBase::VOnActive()
{
}

void AProjectileActorBase::VOnInActive()
{
	OnActorInactivated.ExecuteIfBound(_poolId);
}

void AProjectileActorBase::VReset()
{
	_elapsedLifeTime = 0.0f;
	_projectileMovementComp->Velocity = FVector::ZeroVector;
	_projectileMovementComp->SetUpdatedComponent(GetRootComponent());
	_projectileMovementComp->SetComponentTickEnabled(true);
}

int AProjectileActorBase::VGetPoolId()
{
	return _poolId;
}

void AProjectileActorBase::VSetPoolId(int poolId)
{
	_poolId = poolId;
}

void AProjectileActorBase::VSetScale(float scale)
{
	_basicScale = scale;
}

void AProjectileActorBase::VSetDamage(float damage)
{
	_damage = damage;
}

void AProjectileActorBase::VSetVelocity(FVector velocity)
{
	_projectileMovementComp->Velocity = velocity;
}
