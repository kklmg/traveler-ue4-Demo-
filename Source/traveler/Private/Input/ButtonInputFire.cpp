// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputFire.h"
#include "Components/ActionComponent.h"

UButtonInputFire::UButtonInputFire()
{
	_bindingName = NSInputBindingName::Fire;
}


void UButtonInputFire::VTMPress()
{
	static UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if(actionComp)
	{
		actionComp->ExecuteAction(EActionType::EACT_Fire);
	}
}

void UButtonInputFire::VTMPressing(float deltaTime)
{
}

void UButtonInputFire::VTMRelease()
{
	static UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if(actionComp)
	{
		actionComp->AbortAction(EActionType::EACT_Fire);
	}
}
