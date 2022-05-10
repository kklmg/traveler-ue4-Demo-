// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputDodge.h"
#include "Components/ActionComponent.h"

UButtonInputDodge::UButtonInputDodge()
{
	_bindingName = NSInputBindingName::Dodge;
}

void UButtonInputDodge::VOnPressed()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->ExecuteAction(EActionType::EACT_Dodge);
	}
}

void UButtonInputDodge::VOnPressing(float deltaTime)
{
}

void UButtonInputDodge::VOnReleased()
{
}