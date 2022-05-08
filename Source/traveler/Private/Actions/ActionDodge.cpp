// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionDodge.h"
#include "Character/CreatureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/CostData.h"
#include "Weapon/WeaponBase.h"
#include "Components/WeaponComponent.h"
#include "Components/ActionComponent.h"


UActionDodge::UActionDodge()
{
	_processName = NSNameAction::DODGE;
	_actionType = EActionType::EACT_Dodge;
	_bIsInstantProcess = false;
	_dodgeSpeed = 250;

	GetCostData()->AddCost(EStatusType::EStatus_Stamina,20);
	
}


bool UActionDodge::VCanExecute()
{
	if (!Super::VCanExecute())return false;
	EMovementMode movementMode = GetActionOwner()->GetCharacterMovement()->MovementMode;
	bool bIsWalking = (movementMode == EMovementMode::MOVE_Walking || movementMode == EMovementMode::MOVE_NavWalking);

	return bIsWalking;
}

void UActionDodge::VTMExecute()
{
	UAnimInstance* animInstance = GetActionOwner()->GetMesh()->GetAnimInstance();

	GetActionComp()->AbortAction(EActionType::EACT_Aim);
	GetActionComp()->AbortAction(EActionType::EACT_Fire);

	if (_aniMontage && animInstance)
	{
		//bind 
		animInstance->OnMontageEnded.AddDynamic(this, &UActionDodge::OnAnimMontageFinished);

		//play montage
		GetActionOwner()->PlayAnimMontage(_aniMontage);
	}

	_shiftDirection = GetActionOwner()->GetVelocity().IsNearlyZero() ?
		GetActionOwner()->GetActorForwardVector() : GetActionOwner()->GetVelocity().GetSafeNormal();

	GetActionOwner()->SetActorRotation(_shiftDirection.Rotation());
}

void UActionDodge::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	GetActionOwner()->AddMovementInput(_shiftDirection, _dodgeSpeed * deltaTime);
}


void UActionDodge::OnAnimMontageFinished(UAnimMontage* montage,bool interrupted)
{
	if(montage != _aniMontage)return;

	GetActionOwner()->GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &UActionDodge::OnAnimMontageFinished);
	SetProcessSucceed();
}