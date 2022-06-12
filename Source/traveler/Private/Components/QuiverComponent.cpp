// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuiverComponent.h"
#include "Actors/ArrowActorBase.h"
#include "GameSystem/ObjectPoolBase.h"


// Sets default values for this component's properties
UQuiverComponent::UQuiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;

	// ...
	_poolSize = 500;
}


// Called when the game starts
void UQuiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_arrowOptionIns = NewObject<UArrowOption>(this,_arrowOptionClass);

	_arrowPool = NewObject<UObjectPoolBase>(this);
	_arrowPool->Initialize(_arrowClass, _poolSize);
}

void UQuiverComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UQuiverComponent::SelectArrowOption(int32 id)
{
	_arrowOptionIns->SetID(id);
	
}

void UQuiverComponent::ScrollArrowOption(int32 ScrollAmount)
{
	_arrowOptionIns->Scroll(ScrollAmount);
}


// Called every frame
void UQuiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	/*if (_arrowPool) 
	{
		_arrowPool->DrawDebugMessage();
	}*/
}

bool UQuiverComponent::SpawnArrows(int count, APawn* instigator, TArray<AArrowActorBase*>& outArray)
{
	int32 num = outArray.Num();
	for (int i = 0; i < count; ++i)
	{
		AArrowActorBase* arrowIns = Cast<AArrowActorBase>(_arrowPool->SpawnActor());
		if (arrowIns)
		{
			arrowIns->SetOwner(GetOwner());
			arrowIns->SetInstigator(instigator);
			arrowIns->VSetVelocity(FVector::ZeroVector);
			arrowIns->SetArrowData(_arrowOptionIns->GetSelection());
			arrowIns->VReset();
			outArray.Add(arrowIns);
		}
	}
	return outArray.Num() > num ? true : false;
}

int32 UArrowOption::VGetSize()
{
	return _options.Num();
}

UArrowData* UArrowOption::GetSelection()
{
	return _options[GetCurID()].GetDefaultObject();
}