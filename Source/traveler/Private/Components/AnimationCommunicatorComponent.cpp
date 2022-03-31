// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AnimationCommunicatorComponent.h"

// Sets default values for this component's properties
UAnimationCommunicatorComponent::UAnimationCommunicatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAnimationCommunicatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_eventBroker = NewObject<UEventBroker>(this);
	
}


// Called every frame
void UAnimationCommunicatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAnimationCommunicatorComponent::PublishEvent(FName eventName, UEventDataBase* eventData)
{
	if (_eventBroker) 
	{
		_eventBroker->Publish(eventName, eventData);
	}
}

bool UAnimationCommunicatorComponent::TryGetEventDelegate(FName eventName, FOnEventPublished& outDelegate)
{
	if (_eventBroker)
	{
		outDelegate = _eventBroker->GetDelegate(eventName);
		return true;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("EventBroker Instance missing"));
		return false;
	}
}

