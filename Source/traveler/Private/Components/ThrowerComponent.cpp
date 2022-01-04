// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ThrowerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Interface/ThrowableInterface.h"
#include "Actors/ThrowableActor.h"

// Sets default values for this component's properties
UThrowerComponent::UThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_direction = FVector::ForwardVector;
	_life = 1.0f;
	_poolSize = 10;
	_throwRate = 5.0f;
}


// Called when the game starts
void UThrowerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &UThrowerComponent::SpawnThrowingActor, _throwRate, true);
	}
	
	
}


// Called every frame
void UThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	
}

void UThrowerComponent::SpawnThrowingActor()
{
	UWorld* world = GetWorld();
	FActorSpawnParameters spawnParameters;
	FTransform spawnTransform = GetOwner() ? GetOwner()->GetTransform() : FTransform::Identity;




	if (_spawnActorClass && world && _spawnedActors.Num() < _poolSize)
	{
		AThrowableActor* actor = world->SpawnActor<AThrowableActor>(_spawnActorClass, spawnTransform, spawnParameters);
		if (actor)
		{
			_spawnedActors.Add(actor);

			GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "thrower Spawned actor");
		}
	}
}


