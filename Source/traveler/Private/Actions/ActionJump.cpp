// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionJump.h"
#include "Character/CreatureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/AnimationModelBase.h"
#include "Components/ActionComponent.h"
#include "Weapon/WeaponBase.h"


UActionJump::UActionJump()
{
	_processName = NSNameAction::JUMP;
	_actionType = EActionType::EACT_Jumping;
	_bIsInstantProcess = false;
	_delayTime = 0.3f;
}

void UActionJump::VTMExecute()
{
	Super::VTMExecute();
	if (GetAnimationViewModel())
	{
		GetAnimationViewModel()->SetBool(NSAnimationDataKey::bWantToJump, true);
	}

	GetActionComp()->AbortAction(EActionType::EACT_Fire);
	GetActionComp()->AbortAction(EActionType::EACT_Aim);
}

void UActionJump::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	if (GetElapsedTime() > _delayTime)
	{
		GetActionOwner()->Jump();
		
		if (GetAnimationViewModel())
		{
			GetAnimationViewModel()->SetBool(NSAnimationDataKey::bWantToJump, false);
		}

		SetProcessSucceed();
	}
}