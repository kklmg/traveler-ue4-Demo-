// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputAim.h"
#include "Components/ActionComponent.h"

UButtonInputAim::UButtonInputAim()
{
	_buttonName = TEXT("Aim");
	_inputMappingName = InputActionName::AIM;
}

void UButtonInputAim::VTMPress()
{
	if (GetActionComp())
	{
		GetActionComp()->ExecuteAction(EActionType::EACT_WeaponStartAim);
	}
}

void UButtonInputAim::VTMPressing(float deltaTime)
{
	if (GetActionComp())
	{
		GetActionComp()->ExecuteAction(EActionType::EACT_WeaponStartAim);
	}
}

void UButtonInputAim::VTMRelease()
{
	if (GetActionComp())
	{
		GetActionComp()->ExecuteAction(EActionType::EACT_WeaponStopAim);
	}
}
