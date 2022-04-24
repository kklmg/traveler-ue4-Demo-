// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputAim.h"
#include "Components/ActionComponent.h"

UButtonInputAim::UButtonInputAim()
{
	_buttonName = TEXT("Aim");
	_inputMappingName = NSNameInputAction::AIM;
}

void UButtonInputAim::VTMPress()
{
	if (GetActionComp())
	{
		GetActionComp()->ExecuteAction(EActionType::EACT_Aim);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("button down"));
}

void UButtonInputAim::VTMPressing(float deltaTime)
{
	if (GetActionComp())
	{
		GetActionComp()->ExecuteAction(EActionType::EACT_Aim);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("button pressing"));
}

void UButtonInputAim::VTMRelease()
{
	if (GetActionComp())
	{
		GetActionComp()->AbortAction(EActionType::EACT_Aim);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("button up"));
}
