// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ProjectileActorBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileActorBase::AProjectileActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	if (_primitiveComp)
	{
		//On Hit 
		_primitiveComp->OnComponentHit.AddDynamic(this, &AProjectileActorBase::VOnHit);

		//On Overlap
		_primitiveComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileActorBase::VOnOverlapBegin);
		_primitiveComp->OnComponentEndOverlap.AddDynamic(this, &AProjectileActorBase::VOnOverlapEnd);

		if(GetInstigator())
		{
			_primitiveComp->MoveIgnoreActors.Add(GetInstigator());
			GetInstigator()->MoveIgnoreActorAdd(this);
		}
	}
}

// Called every frame
void AProjectileActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_bIsActive == false) return;

	_elapsedLifeTime += DeltaTime;
	if (_bHasLife && _elapsedLifeTime > _lifeTime)
	{
		VDeactivate();
	}
}

void AProjectileActorBase::VSetLife(float life)
{
	_lifeTime = life;
}

bool AProjectileActorBase::VIsActive()
{
	return _bIsActive;
}

bool AProjectileActorBase::VActivate()
{
	if(!_bIsActive)
	{
		_bIsActive = true;
		SetActorTickEnabled(true);
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);

		VReset();
		return true;
	}
	else
	{
		return false;
	}
}

bool AProjectileActorBase::VDeactivate()
{
	if (_bIsActive)
	{
		_bIsActive = false;

		SetActorTickEnabled(false);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);

		_OnObjectInactiveDelegate.ExecuteIfBound(_poolId);

		if (_bIsMarkDead)
		{
			Destroy();
		}
		return true;
	}
	else
	{
		return false;
	}
}

void AProjectileActorBase::VReset()
{
	_elapsedLifeTime = 0.0f;
	_projectileMovementComp->Velocity = FVector::ZeroVector;
	_projectileMovementComp->SetUpdatedComponent(GetRootComponent());
	_projectileMovementComp->SetComponentTickEnabled(true);
	_primitiveComp->MoveIgnoreActors.Empty();

	if (GetInstigator() && _bIgnoreInstigator)
	{
		_primitiveComp->IgnoreActorWhenMoving(GetInstigator(), true);
		GetInstigator()->MoveIgnoreActorAdd(this);
	}
}

void AProjectileActorBase::FellOutOfWorld(const UDamageType& damageType)
{
	VDeactivate();
}

int AProjectileActorBase::VGetPoolId()
{
	return _poolId;
}

void AProjectileActorBase::VSetPoolId(int poolId)
{
	_poolId = poolId;
}

FOnObjectInactive* AProjectileActorBase::VGetObjectInactiveDelegate()
{
	return &_OnObjectInactiveDelegate;
}

void AProjectileActorBase::VMarkDestroy()
{
	_bIsMarkDead = true;
	if (_bIsMarkDead && _bIsActive == false)
	{
		Destroy();
	}
}

void AProjectileActorBase::VSetScale(float scale)
{
	SetActorScale3D(FVector(scale,scale,scale));
}

void AProjectileActorBase::VSetDamage(float damage)
{
	_damageData.Damage = damage;
}

void AProjectileActorBase::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AProjectileActorBase::VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AProjectileActorBase::VOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AProjectileActorBase::VSetVelocity(FVector velocity)
{
	_projectileMovementComp->MaxSpeed = velocity.Size();
	_projectileMovementComp->Velocity = velocity;
}
