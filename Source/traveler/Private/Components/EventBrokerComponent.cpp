// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EventBrokerComponent.h"

// Sets default values for this component's properties
UEventBrokerComponent::UEventBrokerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}

void UEventBrokerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called when the game starts
void UEventBrokerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UEventBrokerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UEventBrokerComponent::RegisterEvent(FName eventName)
{
	return CreateOrGetEventBroker()->RegisterEvent(eventName);
}

bool UEventBrokerComponent::ContainsRegisteredEvent(FName eventName)
{
	return CreateOrGetEventBroker()->ContainsRegisteredEvent(eventName);
}

bool UEventBrokerComponent::PublishEvent(FName eventName, UObject* data)
{
	return CreateOrGetEventBroker()->PublishEvent(eventName, data);
}

FMD_UObjectSignature* UEventBrokerComponent::GetEventDelegate(FName eventName)
{
	return CreateOrGetEventBroker()->GetEventDelegate(eventName);
}

FMD_UObjectSignature& UEventBrokerComponent::RegisterAndGetEventDelegate(FName eventName)
{
	return CreateOrGetEventBroker()->RegisterAndGetEventDelegate(eventName);
}

UEventBroker* UEventBrokerComponent::CreateOrGetEventBroker()
{
	if (_eventBrokerIns == nullptr)
	{
		_eventBrokerIns = NewObject<UEventBroker>(this);
		checkf(_eventBrokerIns != nullptr, TEXT("missing instance of EventBroker"));
	}
	return _eventBrokerIns;
}

