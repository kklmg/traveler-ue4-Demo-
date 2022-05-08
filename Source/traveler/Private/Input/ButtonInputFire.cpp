// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputFire.h"
#include "Components/ActionComponent.h"

UButtonInputFire::UButtonInputFire()
{
	_bindingName = NSInputBindingName::Fire;
}


void UButtonInputFire::VTMOnPressed()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if(actionComp)
	{
		actionComp->ExecuteAction(EActionType::EACT_Fire);
	}
}

void UButtonInputFire::VTMOnPressing(float deltaTime)
{
}

void UButtonInputFire::VTMOnReleased()
{
	UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if(actionComp)
	{
		actionComp->AbortAction(EActionType::EACT_Fire);
	}
}
