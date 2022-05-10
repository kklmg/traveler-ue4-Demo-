// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputFire.h"
#include "Components/ActionComponent.h"

UButtonInputFire::UButtonInputFire()
{
	_bindingName = NSInputBindingName::Fire;
}


void UButtonInputFire::VOnPressed()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if(actionComp)
	{
		actionComp->ExecuteAction(EActionType::EACT_Fire);
	}
}

void UButtonInputFire::VOnPressing(float deltaTime)
{
}

void UButtonInputFire::VOnReleased()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if(actionComp)
	{
		actionComp->AbortAction(EActionType::EACT_Fire);
	}
}
