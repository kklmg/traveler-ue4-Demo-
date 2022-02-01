// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionJump.h"
#include "Components/AttributeComponent.h"
#include "Character/CreatureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UActionJump::UActionJump()
{
	_actionName = ActionName::JUMP;
	_actionType = EActionType::EACT_Jumping;
	_delayTime = 0.3f;
}

void UActionJump::VTMExecute()
{
	Super::VTMExecute();
	if (_animationModelProviderInterface)
	{
		_animationModelProviderInterface->VGetAnimationModelRef().bWantToJump = true;
	}

	FTimerHandle jumpTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(jumpTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		GetActionOwner()->Jump();

		if (_animationModelProviderInterface)
		{
			_animationModelProviderInterface->VGetAnimationModelRef().bWantToJump = false;
		}

		GetWorld()->GetTimerManager().ClearTimer(jumpTimerHandle);
	}), _delayTime, false);
}

void UActionJump::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}