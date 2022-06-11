// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SphereThrowerComponent.h"
#include "Interface/ThrowerDataProviderInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
USphereThrowerComponent::USphereThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USphereThrowerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	IThrowerDataProviderInterface* throwerDataProviderInterface = GetOwner<IThrowerDataProviderInterface>();
	if (throwerDataProviderInterface)
	{
		_throwerData = throwerDataProviderInterface->VGetThrowerData();
	}
}


// Called every frame
void USphereThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(_bIsThrowing)
	{
		_elapsedTime += DeltaTime;

		while (_elapsedTimeFromLastTracing > _tracingInterval)
		{
			SphereTracing();
			_elapsedTimeFromLastTracing -= _tracingInterval;
		}
	}
}

void USphereThrowerComponent::VSetSpawningLocation(FVector location)
{
}

void USphereThrowerComponent::VSetSpawningActorScale(float scale)
{
}

void USphereThrowerComponent::VSetThrowingDirection(FVector direction)
{
}

void USphereThrowerComponent::VSetSpeed(float speed)
{
}

void USphereThrowerComponent::VSetLife(float life)
{
}

void USphereThrowerComponent::VStartThrowing()
{
	_bIsThrowing = true;
}

void USphereThrowerComponent::VStopThrowing()
{
	_bIsThrowing = false;
	_elapsedTime = 0.0f;
	_elapsedTimeFromLastTracing = 0.0f;
}

void USphereThrowerComponent::SphereTracing()
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




