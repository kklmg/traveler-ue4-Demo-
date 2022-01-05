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
	_velocity = FVector::ForwardVector * 1000;
	_life = 1.0f;
	_poolSize = 10;
	_throwingRate = 5.0f;
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


}

void UThrowerComponent::SetSpawningTransform(FTransform transform)
{
	GetOwner()->SetActorTransform(transform);
}

void UThrowerComponent::VSetVelocity(FVector velocity)
{
	_velocity = velocity;
}

void UThrowerComponent::VSetLife(float life)
{
	_life = life;
}

void UThrowerComponent::SetThrowingOptions(FVector velocity, float life, float rate)
{
	_velocity = velocity;
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
		FTransform spawnTransform = owner ? owner->GetTransform() : FTransform::Identity;

		actor->SetActorTransform(spawnTransform);
		actor->VSetLife(_life);
		actor->VSetVelocity(_velocity);
		actor->VSetIsActive(true);

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


	
	
	

	



