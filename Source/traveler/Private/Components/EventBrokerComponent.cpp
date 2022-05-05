// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EventBrokerComponent.h"
#include "Event/EventBroker.h"

// Sets default values for this component's properties
UEventBrokerComponent::UEventBrokerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
	if (_eventBrokerIns == nullptr)
	{
		_eventBrokerIns = CreateDefaultSubobject<UEventBroker>(TEXT("EventBrokerIns"));
		checkf(_eventBrokerIns != nullptr, TEXT("missing instance of EventBroker"));
	}
}

void UEventBrokerComponent::InitializeComponent()
{
	
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
	return _eventBrokerIns->RegisterEvent(eventName);
}

bool UEventBrokerComponent::ContainsRegisteredEvent(FName eventName)
{
	return _eventBrokerIns->ContainsRegisteredEvent(eventName);
}

bool UEventBrokerComponent::PublishEvent(FName eventName, UObject* data)
{
	return _eventBrokerIns->PublishEvent(eventName, data);
}

FMD_OnEventPublished* UEventBrokerComponent::GetEventDelegate(FName eventName)
{
	return _eventBrokerIns->GetEventDelegate(eventName);
}

FMD_OnEventPublished& UEventBrokerComponent::RegisterAndGetEventDelegate(FName eventName)
{
	return _eventBrokerIns->RegisterAndGetEventDelegate(eventName);
}

