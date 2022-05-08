// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputAim.h"
#include "Components/ActionComponent.h"

UButtonInputAim::UButtonInputAim()
{
	_bindingName = NSInputBindingName::Aim;
}

void UButtonInputAim::VTMOnPressed()
{
	static UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->ExecuteAction(EActionType::EACT_Aim);
	}
}

void UButtonInputAim::VTMOnPressing(float deltaTime)
{
	static UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	{
		actionComp->ExecuteAction(EActionType::EACT_Aim);
	}
}

void UButtonInputAim::VTMOnReleased()
{
	static UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->AbortAction(EActionType::EACT_Aim);
	}
}
