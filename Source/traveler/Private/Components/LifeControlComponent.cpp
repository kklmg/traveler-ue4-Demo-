// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LifeControlComponent.h"
#include "Condition/CompositeActorCondition.h"
#include "Components/EventBrokerComponent.h"


// Sets default values for this component's properties
ULifeControlComponent::ULifeControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;
}


void ULifeControlComponent::InitializeComponent()
{
	Super::InitializeComponent();

	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));
	if (_eventBrokerComp)
	{
		_eventBrokerComp->RegisterEvent(NSEventData::ActorLifeStateChanged::Name);
		_lifeStateChangedData = NewObject<NSEventData::ActorLifeStateChanged::Type>(this);
		check(_lifeStateChangedData);
	}

	_ConditionIsAliveIns = _lifeConditionClass ?
		NewObject<UCompositeActorCondition>(this, _lifeConditionClass) : NewObject<UCompositeActorCondition>(this);

	check(_ConditionIsAliveIns);
}

// Called when the game starts
void ULifeControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	if (_eventBrokerComp)
	{
		//destroy actor after death effect finished
		_eventBrokerComp->SubscribeEvent<ULifeControlComponent>
			(NSEventData::ActorDeathEffectFinished::Name, this, &ULifeControlComponent::OnActorDeathEffectFinished);
	}

	_ConditionIsAliveIns->SetActor(GetOwner());
	_ConditionIsAliveIns->Initialize();
	_ConditionIsAliveIns->OnValidatedDelegate.AddUObject(this, &ULifeControlComponent::OnLifeStateChanged);
	_ConditionIsAliveIns->Validate();
}

void ULifeControlComponent::OnLifeStateChanged(bool isAlive)
{
	//publish actorLife Changed Event to other actor components
	if (_eventBrokerComp)
	{
		_lifeStateChangedData->Value = isAlive;
		_eventBrokerComp->PublishEvent(NSEventData::ActorLifeStateChanged::Name, _lifeStateChangedData);
	}

	if (_bDestroyAfterDead && isAlive == false)
	{
		if (_eventBrokerComp == nullptr || _eventBrokerComp->ContainsRegisteredEvent(NSEventData::ActorDeathEffectFinished::Name) == false)
		{
			GetOwner()->Destroy();
		}
	}
}

void ULifeControlComponent::OnActorDeathEffectFinished(UObject* baseData)
{
	auto eventData = Cast<NSEventData::ActorDeathEffectFinished::Type>(baseData);
	if (_bDestroyAfterDead && eventData && eventData->Value == true)
	{
		GetOwner()->Destroy();
	}
}


// Called every frame
void ULifeControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULifeControlComponent::IsAlive()
{
	return _ConditionIsAliveIns ? _ConditionIsAliveIns->GetResult() : true;
}


