// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EffectControllerComponent.h"
#include "GameFramework/Character.h"
#include "Effet/EffectPlayerBase.h"
#include "Components/ExTransformProviderComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Event/EventData.h"

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

	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));
	if (_eventBrokerComp && _eventBrokerComp->ContainsRegisteredEvent(NSEvent::ActorLifeStateChanged::Name))
	{
		_eventBrokerComp->GetEventDelegate(NSEvent::ActorLifeStateChanged::Name)->AddUObject(this, &UEffectControllerComponent::OnActorLifeStateChanged);
		_eventData_DeathEffectFinished = NewObject<UDataBool>(this);

		_eventBrokerComp->RegisterEvent(NSEvent::ActorDeathEffectFinished::Name);
	}
}

// Called when the game starts
void UEffectControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	auto pEffectFinishedDelegate = GetEffectFinishedDelegate(EEffectType::EEffectType_Dissolve);
	if(pEffectFinishedDelegate)
	{
		pEffectFinishedDelegate->AddUObject(this, &UEffectControllerComponent::OnActorDeathEffectFinished);
	}


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

FMD_BoolValueChangeSignature* UEffectControllerComponent::GetEffectFinishedDelegate(EEffectType effectType)
{
	if(_effectPlayerInsMap.Contains(effectType))
	{
		return &_effectPlayerInsMap[effectType]->GetEffectFinishedDelegate();
	}
	else
	{
		return nullptr;
	}
}

void UEffectControllerComponent::SetupDynamicMaterial(int32 elementIndex)
{
	check(GetOwner());

	UMeshComponent* meshComp = Cast<UMeshComponent>(GetOwner()->GetComponentByClass(UMeshComponent::StaticClass()));
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

void UEffectControllerComponent::OnActorLifeStateChanged(UObject* data)
{
	auto isAliveData = Cast<NSEvent::ActorLifeStateChanged::DataType>(data);

	if (isAliveData)
	{
		isAliveData->Value ? StopEffect(EEffectType::EEffectType_Dissolve, 0) : PlayEffect(EEffectType::EEffectType_Dissolve,0);
	}
}

void UEffectControllerComponent::OnActorDeathEffectFinished(bool bForward)
{
	if(_eventBrokerComp)
	{
		_eventData_DeathEffectFinished->Value = bForward;
		_eventBrokerComp->PublishEvent(NSEvent::ActorDeathEffectFinished::Name,_eventData_DeathEffectFinished);
	}
}


