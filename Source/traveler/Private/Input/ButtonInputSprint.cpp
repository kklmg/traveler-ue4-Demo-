// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputSprint.h"
#include "Components/ActionComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"

UButtonInputSprint::UButtonInputSprint()
{
	_buttonName = TEXT("Sprint");
	_inputMappingName = InputActionName::SPRINT;
}

void UButtonInputSprint::VTMPress()
{
	check(GetActionComp())
	GetActionComp()->GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_WantToSprint, true);	
}

void UButtonInputSprint::VTMPressing(float deltaTime)
{
}

void UButtonInputSprint::VTMRelease()
{
	check(GetActionComp())
	GetActionComp()->GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_WantToSprint, false);
}