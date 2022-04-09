// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ReactiveCondition.h"
#include "Interface/EventBrokerInterface.h"

void UReactiveCondition::SubscribeEvents(IEventBrokerInterface* eventBroker)
{
	if (eventBroker)
	{
		for (FName eventName : _eventNames)
		{
			eventBroker->VGetEventDelegate(eventName).AddUObject(this, &UReactiveCondition::Notify);
		}
	}
}

bool UReactiveCondition::VValidate(UEventDataBase* eventData)
{
	return Super::VValidate(eventData);
}

void UReactiveCondition::Notify(UEventDataBase* eventData)
{
	OnValidate.Broadcast(VValidate(eventData));
}
