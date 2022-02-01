// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputAim.h"

void UButtonInputAim::VTMPress()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_WeaponStartAim);
	}
}

void UButtonInputAim::VTMPressing(float deltaTime)
{
}

void UButtonInputAim::VTMRelease()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_WeaponStopAim);
	}
}
