// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputDodge.h"
#include "Components/ActionComponent.h"

UButtonInputDodge::UButtonInputDodge()
{
	_buttonName = TEXT("Dodge");
	_inputMappingName = NSNameInputAction::DODGE;
}

void UButtonInputDodge::VTMPress()
{
	check(GetActionComp())
	GetActionComp()->ExecuteAction(EActionType::EACT_Dodge);
}

void UButtonInputDodge::VTMPressing(float deltaTime)
{
}

void UButtonInputDodge::VTMRelease()
{
}