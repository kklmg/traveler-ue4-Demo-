// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EffectControllerComponent.h"
#include "GameFramework/Character.h"
#include "Effet/EffectPlayerBase.h"
#include "Components/ExtraTransformProviderComponent.h"

// Sets default values for this component's properties
UEffectControllerComponent::UEffectControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;
}

void UEffectControllerComponent::InitializeComponent()
{
	SetupDynamicMaterial(0);

	for (auto& efffectPlayerclass : _effectPlayerClassMap)
	{
		if (efffectPlayerclass.Value)
		{
			UEffectPlayerBase* effectPlayerIns = NewObject<UEffectPlayerBase>(this, efffectPlayerclass.Value);
			effectPlayerIns->VInitialize(GetOwner(), _MID);
			_effectPlayerInsMap.Add(efffectPlayerclass.Key, effectPlayerIns);
		}
	}
}

// Called when the game starts
void UEffectControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UEffectControllerComponent::PlayEffect(EEffectType effectType, uint8 effectOption)
{
	if (_effectPlayerInsMap.Contains(effectType))
	{
		_effectPlayerInsMap[effectType]->VPlayEffect(effectOption);
	}

	else
	{
		UE_LOG(LogTemp,Warning,TEXT("no effect class"));
	}
}

void UEffectControllerComponent::StopEffect(EEffectType effectType, uint8 effectOption)
{
	if (_effectPlayerInsMap.Contains(effectType))
	{
		_effectPlayerInsMap[effectType]->VStopEffect(effectOption);
	}
}

void UEffectControllerComponent::SetupDynamicMaterial(int32 elementIndex)
{
	ACharacter* character = GetOwner<ACharacter>();
	if (!character) return;
	
	USkeletalMeshComponent* meshComp = character->GetMesh();
	if (!meshComp) return;

	UMaterialInterface* matInterface = meshComp->GetMaterial(elementIndex);
	if (!matInterface) return;

	_MID = UMaterialInstanceDynamic::Create(matInterface, this);

	meshComp->SetMaterial(elementIndex,_MID);
}

// Called every frame
void UEffectControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	for (auto& efffectPlayerIns : _effectPlayerInsMap)
	{
		if (efffectPlayerIns.Value)
		{
			efffectPlayerIns.Value->VTick(DeltaTime);
		}
	}
}

