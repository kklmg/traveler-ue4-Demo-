// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ThrowerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Interface/ThrowableInterface.h"
#include "Interface/ThrowerDataProviderInterface.h"
#include "Actors/ProjectileActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameSystem/ObjectPoolBase.h"


// Sets default values for this component's properties
UThrowerComponent::UThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_elapsedTime = 0.0f;
	_poolSize = 256;
}


// Called when the game starts
void UThrowerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_throwerDataProvider = GetOwner<IThrowerDataProviderInterface>();
	_pool = NewObject<UObjectPoolBase>(this);
	_pool->Initialize(_spawningActorClass, _poolSize);


	if (GetWorld() && _throwerDataProvider)
	{
		GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &UThrowerComponent::SpawnThrowingActor,
			_throwerDataProvider->VGetThrowerData().ThrowingRate, true);
	}
}


// Called every frame
void UThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	_elapsedTime += DeltaTime;
}


void UThrowerComponent::SpawnThrowingActor()
{
	if (_throwerDataProvider == nullptr)return;
	if (isSpawnable() == false) return;

	AProjectileActor* actor = _pool->SpawnObject<AProjectileActor>();
	
	if (actor)
	{
		FThrowerData data = _throwerDataProvider->VGetThrowerData();

		AActor* owner = GetOwner();
		FTransform ownerTransform = owner ? owner->GetTransform() : FTransform::Identity;
		FVector forward = owner ? owner->GetActorForwardVector() : FVector::ForwardVector;

		actor->SetActorTransform(ownerTransform);
		actor->VSetLife(data.Life);
		actor->VSetScale(data.Scale);
		actor->VSetDamage(data.Damage);
		actor->VSetVelocity(forward * data.Speed);
		actor->VSetScaleCurve(data.ScaleCurve);

		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "thrower Spawned actor");
	}
}


bool UThrowerComponent::isSpawnable()
{
	return _pool ? _pool->IsSpawnable() : false;
}

void UThrowerComponent::StopSpawning()
{
	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}
	
void UThrowerComponent::SphereTracing()
{
	if (_throwerDataProvider == nullptr)return;

	FThrowerData data = _throwerDataProvider->VGetThrowerData();

	float traceDistance = FMath::Clamp(data.Speed * _elapsedTime, 0.0f, data.Speed * data.Life);

	float sphereRadius = data.ScaleCurve ? data.ScaleCurve->GetFloatValue(_elapsedTime / data.Life) : 10.0f;

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
		hitRes.Actor->TakeDamage(data.Damage, damageEvent, instigator ? instigator->GetController() : nullptr, instigator);
	}
}


