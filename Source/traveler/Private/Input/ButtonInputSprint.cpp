// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputSprint.h"

UButtonInputSprint::UButtonInputSprint()
{
	_buttonName = TEXT("Sprint");
	_inputMappingName = InputActionName::SPRINT;
}

void UButtonInputSprint::VTMPress()
{
	if (_actionInterface)
	{
		_actionInterface->VGetActionBlackBoard()->WriteData_Bool(EActionData::EACTD_WantToSprint, true);
	}
}

void UButtonInputSprint::VTMPressing(float deltaTime)
{
}

void UButtonInputSprint::VTMRelease()
{
	if (_actionInterface)
	{
		_actionInterface->VGetActionBlackBoard()->WriteData_Bool(EActionData::EACTD_WantToSprint, false);
	}
}