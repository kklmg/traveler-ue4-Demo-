// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputFire.h"
#include "Components/ActionComponent.h"

UButtonInputFire::UButtonInputFire()
{
	_buttonName = TEXT("Fire");
	_inputMappingName = NSNameInputAction::FIRE;
}


void UButtonInputFire::VTMPress()
{
	check(GetActionComp())
	GetActionComp()->ExecuteAction(EActionType::EACT_Fire);
}

void UButtonInputFire::VTMPressing(float deltaTime)
{
}

void UButtonInputFire::VTMRelease()
{
	check(GetActionComp())
	GetActionComp()->AbortAction(EActionType::EACT_Fire);
}
