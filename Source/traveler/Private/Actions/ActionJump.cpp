// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionJump.h"
#include "Components/AttributeComponent.h"
#include "Character/CreatureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UActionJump::UActionJump()
{
	_actionName = ActionName::JUMP;
	_actionType = EActionType::EACT_Jumping;
	_delayTime = 0.5f;
}

void UActionJump::VExecute()
{
	Super::VExecute();
	if (_animationModelProviderInterface)
	{
		_animationModelProviderInterface->VGetAnimationModel().bWantToJump = true;
	}

	FTimerHandle jumpTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(jumpTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		GetActionOwner()->Jump();

		if (_animationModelProviderInterface)
		{
			_animationModelProviderInterface->VGetAnimationModel().bWantToJump = false;
		}

		GetWorld()->GetTimerManager().ClearTimer(jumpTimerHandle);
	}), _delayTime, false);
}

void UActionJump::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}


//void UActionJump::OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
//{
//	if (/*PrevMovementMode ==  && */Character->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
//	{
//		//Get My Character
//		Character->StopJumping();
//
//		if (_aniMontage != nullptr)
//		{
//			Character->StopAnimMontage(_aniMontage);
//		}
//		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("landed"));
//		Character->MovementModeChangedDelegate.RemoveDynamic(this, &UActionJump::OnMovementModeChanged);
//	}
//}