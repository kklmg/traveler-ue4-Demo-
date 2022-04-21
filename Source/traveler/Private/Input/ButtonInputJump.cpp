// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputJump.h"
#include "Components/ActionComponent.h"

UButtonInputJump::UButtonInputJump()
{
	_buttonName = TEXT("Jump");
	_inputMappingName = NSNameInputAction::JUMP;
}

void UButtonInputJump::VTMPress()
{
	check(GetActionComp())
	GetActionComp()->ExecuteAction(EActionType::EACT_Jumping);
}

void UButtonInputJump::VTMPressing(float deltaTime)
{
}

void UButtonInputJump::VTMRelease()
{

}