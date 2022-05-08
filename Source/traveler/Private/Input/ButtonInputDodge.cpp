// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputDodge.h"
#include "Components/ActionComponent.h"

UButtonInputDodge::UButtonInputDodge()
{
	_bindingName = NSInputBindingName::Dodge;
}

void UButtonInputDodge::VTMOnPressed()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->ExecuteAction(EActionType::EACT_Dodge);
	}
}

void UButtonInputDodge::VTMOnPressing(float deltaTime)
{
}

void UButtonInputDodge::VTMOnReleased()
{
}