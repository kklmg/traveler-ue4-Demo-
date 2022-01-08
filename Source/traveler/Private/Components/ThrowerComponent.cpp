// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ThrowerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Interface/ThrowableInterface.h"
#include "Actors/ThrowableActor.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UThrowerComponent::UThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_speed = 1000;
	_life = 1.0f;
	_poolSize = 10;
	_throwingRate = 5.0f;
	_coneAngle = 5;

	_elapsedTime = 0.0f;
}


// Called when the game starts
void UThrowerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &UThrowerComponent::SpawnThrowingActor, _throwingRate, true);
	}


}


// Called every frame
void UThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	_elapsedTime += DeltaTime;


}

void UThrowerComponent::SetSpeed(float speed)
{
	_speed = speed;
}

void UThrowerComponent::SetLife(float life)
{
	_life = life;
}

void UThrowerComponent::SetThrowingOptions(float speed, float life, float rate)
{
	_speed = speed;
	_life = life;
	_throwingRate = rate;

}

void UThrowerComponent::SpawnThrowingActor()
{
	if (isSpawnable() == false) return;

	AThrowableActor* actor = CreateOrGetInactivatedActor();
	
	if (actor)
	{
		AActor* owner = GetOwner();
		FTransform ownerTransform = owner ? owner->GetTransform() : FTransform::Identity;
		FVector forward = owner ? owner->GetActorForwardVector() : FVector::ForwardVector;

		actor->SetActorTransform(ownerTransform);
		actor->VSetLife(_life);
		actor->VSetVelocity(forward * _speed);
		actor->VSetIsActive(true);
		actor->VSetScaleCurve(_scaleCurve);

		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "thrower Spawned actor");
	}
	
}


bool UThrowerComponent::isSpawnable()
{
	return _spawnedActors.Num() < _poolSize || _inactivatedActorIndicies.Num() != 0;
}

void UThrowerComponent::OnSpawnedActorInactivated(int poolId)
{
	_inactivatedActorIndicies.Add(poolId);
}

AThrowableActor* UThrowerComponent::CreateOrGetInactivatedActor()
{
	//try get reusable actor 
	if (_inactivatedActorIndicies.Num() != 0)
	{
		int lastIndex = _inactivatedActorIndicies.Pop();

		if(lastIndex>_spawnedActors.Num()-1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Something Went wrong at pooling logic"));
			return nullptr;
		}
		
		return _spawnedActors[lastIndex];
	}

	if (_spawningActorClass == nullptr) return nullptr;

	UWorld* world = GetWorld();
	if (world == nullptr) return nullptr;


	FActorSpawnParameters spawnParameters;
	
	//make instance
	AThrowableActor* actor = world->SpawnActor<AThrowableActor>(_spawningActorClass,spawnParameters);
	
	if (actor)
	{
		actor->VSetPoolId(_spawnedActors.Num());
		actor->OnActorInactivated.BindUFunction(this,FName(TEXT("OnSpawnedActorInactivated")));
		_spawnedActors.Add(actor);
	}

	return actor;
}


	
void UThrowerComponent::SphereTracing()
{
	float traceDistance = FMath::Clamp(_speed * _elapsedTime, 0.0f, _speed * _life);

	float sphereRadius = _scaleCurve ? _scaleCurve->GetFloatValue(_elapsedTime / _life) : 10.0f;

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
		hitRes.Actor->TakeDamage(_damage, damageEvent, instigator ? instigator->GetController() : nullptr, instigator);
	}
}


