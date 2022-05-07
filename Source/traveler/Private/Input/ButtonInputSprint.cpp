// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputSprint.h"
#include "Components/ActionComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Components/EventBrokerComponent.h"

UButtonInputSprint::UButtonInputSprint()
{
	_bindingName = NSInputBindingName::Sprint;
}

void UButtonInputSprint::VTMPress()
{
	static UEventBrokerComponent* eventBrokerComp = GetInputPreset()->GetEventBrokerComp();
	if (eventBrokerComp)
	{
		//eventBrokerComp->PublishEvent(ns)
	}
}

void UButtonInputSprint::VTMPressing(float deltaTime)
{
}

void UButtonInputSprint::VTMRelease()
{
	static UEventBrokerComponent* eventBrokerComp = GetInputPreset()->GetEventBrokerComp();
	if (eventBrokerComp)
	{
		//eventBrokerComp->PublishEvent(ns)
	}
}