// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ProjectileThrowerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Interface/ThrowableInterface.h"
#include "Interface/ThrowerDataProviderInterface.h"
#include "Actors/ProjectileActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameSystem/ObjectPoolBase.h"


// Sets default values for this component's properties
UProjectileThrowerComponent::UProjectileThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_elapsedTime = 0.0f;
	_poolSize = 256;
}


void UProjectileThrowerComponent::InitializeComponent()
{

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

	check(GetWorld());

	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this,
		&UProjectileThrowerComponent::SpawnProjectile, _throwerData.ThrowingRate, true);

}


// Called every frame
void UProjectileThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	_elapsedTime += DeltaTime;
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

void UProjectileThrowerComponent::VAutoDestroy()
{

}

void UProjectileThrowerComponent::SpawnProjectile()
{
	check(GetOwner());
	check(_pool);

	if (isSpawnable() == false) return;
	AProjectileActor* actor = _pool->SpawnObject<AProjectileActor>();

	if (actor)
	{
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

void UProjectileThrowerComponent::StopSpawning()
{
	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void UProjectileThrowerComponent::SphereTracing()
{
	float traceDistance = FMath::Clamp(_throwerData.Speed * _elapsedTime, 0.0f, _throwerData.Speed * _throwerData.Life);

	float sphereRadius = _throwerData.ScaleCurve ? _throwerData.ScaleCurve->GetFloatValue(_elapsedTime / _throwerData.Life) : 10.0f;

	FVector traceStart = GetOwner()->GetActorLocation();
	FVector traceDir = GetOwner()->GetActorQuat().Vector();
	FVector traceEnd = traceStart + traceDir * traceDistance;

	TArray<AActor*> ignoredActors;
	ignoredActors.Add(GetOwner());

	TArray<FHitResult> hitResults;

	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), traceStart, traceEnd, sphereRadius,
		ETraceTypeQuery::TraceTypeQuery1, false, ignoredActors, EDrawDebugTrace::ForOneFrame, hitResults, true);

	for (FHitResult hitRes : hitResults)
	{
		if (hitRes.Actor == nullptr)
		{
			continue;
		}
		FDamageEvent damageEvent;
		APawn* instigator = GetOwner()->GetInstigator();
		hitRes.Actor->TakeDamage(_throwerData.Damage, damageEvent, instigator ? instigator->GetController() : nullptr, instigator);
	}
}


