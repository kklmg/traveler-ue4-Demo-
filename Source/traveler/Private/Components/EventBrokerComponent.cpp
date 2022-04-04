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
}

void UEventBrokerComponent::InitializeComponent()
{
	_eventBroker = NewObject<UEventBroker>(this);
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

void UEventBrokerComponent::PublishEvent(FName eventName, UEventDataBase* eventData)
{
	checkf(_eventBroker != nullptr, TEXT("missing instance of EventBroker"));

	_eventBroker->Publish(eventName, eventData);
}

FOnEventPublished& UEventBrokerComponent::GetEventDelegate(FName eventName)
{
	checkf(_eventBroker != nullptr, TEXT("missing instance of EventBroker"));

	return _eventBroker->GetDelegate(eventName);
}

