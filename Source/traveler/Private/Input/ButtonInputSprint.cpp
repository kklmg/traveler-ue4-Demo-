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
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_WantToSprint, true);
	}
}

void UButtonInputSprint::VTMOnPressing(float deltaTime)
{
}

void UButtonInputSprint::VTMOnReleased()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_WantToSprint, false);
	}
}