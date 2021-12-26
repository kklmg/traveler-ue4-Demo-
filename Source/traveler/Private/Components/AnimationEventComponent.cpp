// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AnimationEventComponent.h"
#include "AnimNotify/AnimNotifyHandler.h"


// Sets default values for this component's properties
UAnimationEventComponent::UAnimationEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAnimationEventComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UAnimationEventComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UAnimNotifyHandler* UAnimationEventComponent::GetHNotifyHandler(EAnimNorifyKey notifyKey)
{
	if (_mapSubscribers.Contains(notifyKey))
	{
		return _mapSubscribers[notifyKey];
	}
	else
	{
		UAnimNotifyHandler* notifyHandler = NewObject<UAnimNotifyHandler>(this);
		_mapSubscribers.Add(notifyKey, notifyHandler);
		return notifyHandler;
	}
}



void UAnimationEventComponent::notifyBegin(EAnimNorifyKey notifyKey, float frameDeltaTime)
{
	if (_mapSubscribers.Contains(notifyKey))
	{
		_mapSubscribers[notifyKey]->OnNotifyBegin.Broadcast(frameDeltaTime);
	}
}

void UAnimationEventComponent::notifyTick(EAnimNorifyKey notifyKey, float frameDeltaTime)
{
	if (_mapSubscribers.Contains(notifyKey))
	{
		_mapSubscribers[notifyKey]->OnNotifyTick.Broadcast(frameDeltaTime);
	}
}

void UAnimationEventComponent::notifyEnd(EAnimNorifyKey notifyKey)
{
	if (_mapSubscribers.Contains(notifyKey))
	{
		_mapSubscribers[notifyKey]->OnNotifyEnd.Broadcast();
	}


}



