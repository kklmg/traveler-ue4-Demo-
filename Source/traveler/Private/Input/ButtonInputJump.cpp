// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputJump.h"
#include "Components/ActionComponent.h"

UButtonInputJump::UButtonInputJump()
{
	_bindingName = NSInputBindingName::Jump;
}

void UButtonInputJump::VTMOnPressed()
{
	static UActionComponent* actionComp = GetInputPreset()->GetActionComp();
	if (actionComp)
	{
		actionComp->ExecuteAction(EActionType::EACT_Jumping);
	}
}

void UButtonInputJump::VTMOnPressing(float deltaTime)
{
}

void UButtonInputJump::VTMOnReleased()
{

}