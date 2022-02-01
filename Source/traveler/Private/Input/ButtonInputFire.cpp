// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputFire.h"

void UButtonInputFire::VTMPress()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_WeaponStartFire);
	}
}

void UButtonInputFire::VTMPressing(float deltaTime)
{
}

void UButtonInputFire::VTMRelease()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(EActionType::EACT_WeaponStopFire);
	}
}
