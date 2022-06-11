// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ProjectileThrowerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Interface/ThrowerDataProviderInterface.h"
#include "Actors/SphereProjectile.h"
#include "GameSystem/ObjectPoolBase.h"
#include "GameSystem/MyGameplayStatics.h"


// Sets default values for this component's properties
UProjectileThrowerComponent::UProjectileThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_poolSize = 256;
}


void UProjectileThrowerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called when the game starts
void UProjectileThrowerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	IThrowerDataProviderInterface* throwerDataProviderInterface = GetOwner<IThrowerDataProviderInterface>();
	if (throwerDataProviderInterface)
	{
		_throwerData = throwerDataProviderInterface->VGetThrowerData();
	}

	_pool = NewObject<UObjectPoolBase>(this);
	_pool->Initialize(_spawningActorClass, _poolSize);

	if(_bSpawnProjectileOnBeginPlay)
	{
		VStartThrowing();
	}
}

void UProjectileThrowerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	check(_pool);
	_pool->EmptyPool();
}


// Called every frame
void UProjectileThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UProjectileThrowerComponent::VSetSpawningLocation(FVector location)
{
}

void UProjectileThrowerComponent::VSetSpawningActorScale(float scale)
{
	_throwerData.Scale = scale;
}

void UProjectileThrowerComponent::VSetThrowingDirection(FVector direction)
{
}

void UProjectileThrowerComponent::VSetSpeed(float speed)
{
	_throwerData.Speed = speed;
}

void UProjectileThrowerComponent::VSetLife(float life)
{
	_throwerData.Life = life;
}

void UProjectileThrowerComponent::VStartThrowing()
{
	check(GetWorld());

	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this,
		&UProjectileThrowerComponent::SpawnProjectile, _throwerData.ThrowingRate, true);
}

void UProjectileThrowerComponent::VStopThrowing()
{
	check(GetWorld());

	if (_timerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
	}
}

void UProjectileThrowerComponent::SpawnProjectile()
{
	check(GetOwner());
	check(_pool);

	if (isSpawnable() == false) return;
	ASphereProjectile* actor = _pool->SpawnObject<ASphereProjectile>();

	if (actor)
	{
		actor->SetInstigator(GetOwner()->GetInstigator());
		actor->SetOwner(GetOwner());
		actor->SetActorTransform(GetOwner()->GetTransform());
		actor->VSetLife(_throwerData.Life);
		actor->VSetScale(_throwerData.Scale);
		actor->VSetDamage(_throwerData.Damage);
		actor->VSetVelocity(GetOwner()->GetActorForwardVector() * _throwerData.Speed);
		actor->VSetScaleCurve(_throwerData.ScaleCurve);
	}
}


bool UProjectileThrowerComponent::isSpawnable()
{
	return _pool ? _pool->IsSpawnable() : false;
}


