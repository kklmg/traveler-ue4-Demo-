// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputDodge.h"

UButtonInputDodge::UButtonInputDodge()
{
	_buttonName = TEXT("Dodge");
	_inputMappingName = InputActionName::DODGE;
}

void UButtonInputDodge::VTMPress()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_Dodge);
	}
}

void UButtonInputDodge::VTMPressing(float deltaTime)
{
}

void UButtonInputDodge::VTMRelease()
{
}