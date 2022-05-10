// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputAim.h"
#include "Components/ActionComponent.h"

UButtonInputAim::UButtonInputAim()
{
	_bindingName = NSInputBindingName::Aim;
}

void UButtonInputAim::VOnPressed()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->ExecuteAction(EActionType::EACT_Aim);
	}
}

void UButtonInputAim::VOnPressing(float deltaTime)
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	{
		actionComp->ExecuteAction(EActionType::EACT_Aim);
	}
}

void UButtonInputAim::VOnReleased()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->AbortAction(EActionType::EACT_Aim);
	}
}
