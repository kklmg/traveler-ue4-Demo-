// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuiverComponent.h"
#include "Actors/ArrowActorBase.h"

// Sets default values for this component's properties
UQuiverComponent::UQuiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuiverComponent::SpawnArrows(int count, APawn* instigator,TArray<AArrowActorBase*>& outArray)
{
	for (int i = 0; i < count; ++i)
	{
		AArrowActorBase* arrowIns = CreateOrGetInactivatedFromPool(instigator);
		if (arrowIns == nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("cant spawn projectile"))
			return;
		}
		arrowIns->VSetVelocity(FVector::ZeroVector);
		arrowIns->VSetIsActive(true);

		outArray.Add(arrowIns);
	}
}


AArrowActorBase* UQuiverComponent::CreateOrGetInactivatedFromPool(APawn* instigator)
{
	//try get reusable actor 
	if (_inactivatedIndicies.Num() != 0)
	{
		int lastIndex = _inactivatedIndicies.Pop();

		if (lastIndex > _arrowPool.Num() - 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Something Went wrong at pooling logic"));
			return nullptr;
		}
		return _arrowPool[lastIndex];
	}

	if (_arrowClass == nullptr)
	{
		return nullptr;
	}

	UWorld* world = GetWorld();
	if (world == nullptr)
	{
		return nullptr;
	}

	//make projectile instance
	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = GetOwner();
	spawnParameters.Instigator = instigator;
	AArrowActorBase* arrowIns = world->SpawnActor<AArrowActorBase>(_arrowClass, spawnParameters);

	if (arrowIns)
	{
		arrowIns->VSetPoolId(_arrowPool.Num());
		arrowIns->OnActorInactivated.BindUFunction(this, FName(TEXT("OnSpawnedActorInactivated")));
		_arrowPool.Add(arrowIns);
	}

	return arrowIns;
}

void UQuiverComponent::OnSpawnedActorInactivated(int poolId)
{
	_inactivatedIndicies.Add(poolId);
}
