// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputAim.h"

UButtonInputAim::UButtonInputAim()
{
	_buttonName = TEXT("Aim");
	_inputMappingName = InputActionName::AIM;
}

void UButtonInputAim::VTMPress()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_WeaponStartAim);
	}
}

void UButtonInputAim::VTMPressing(float deltaTime)
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_WeaponStartAim);
	}
}

void UButtonInputAim::VTMRelease()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_WeaponStopAim);
	}
}
