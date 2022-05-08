// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputSprint.h"
#include "Components/ActionComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Components/EventBrokerComponent.h"

UButtonInputSprint::UButtonInputSprint()
{
	_bindingName = NSInputBindingName::Sprint;
}

void UButtonInputSprint::VTMOnPressed()
{
	static UEventBrokerComponent* eventBrokerComp = GetInputPreset()->GetEventBrokerComp();
	if (eventBrokerComp)
	{
		//eventBrokerComp->PublishEvent(ns)
	}
}

void UButtonInputSprint::VTMOnPressing(float deltaTime)
{
}

void UButtonInputSprint::VTMOnReleased()
{
	static UEventBrokerComponent* eventBrokerComp = GetInputPreset()->GetEventBrokerComp();
	if (eventBrokerComp)
	{
		//eventBrokerComp->PublishEvent(ns)
	}
}