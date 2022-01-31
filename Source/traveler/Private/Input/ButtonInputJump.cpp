// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputJump.h"

UButtonInputJump::UButtonInputJump()
{
	_buttonName = TEXT("Jump");
	_inputMappingName = InputActionName::JUMP;
}

void UButtonInputJump::VTMPress()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_Jumping);
	}
}

void UButtonInputJump::VTMPressing(float deltaTime)
{
}

void UButtonInputJump::VTMRelease()
{

}