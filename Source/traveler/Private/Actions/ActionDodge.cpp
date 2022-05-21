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
	_processName = NSNameAction::dodge;
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

	return bIsWalking && GetActionComp()->IsActionAlive(EActionType::EACT_Jumping) == false;
}

void UActionDodge::VOnExecute()
{
	Super::VOnExecute();
	UAnimInstance* animInstance = GetActionOwner()->GetMesh()->GetAnimInstance();

	GetActionComp()->AbortAction(EActionType::EACT_Aim);
	GetActionComp()->AbortAction(EActionType::EACT_Fire);

	if (_aniMontage && animInstance)
	{
		//bind 
		animInstance->OnMontageBlendingOut.AddDynamic(this, &UActionDodge::OnAnimMontageFinished);

		//play montage
		GetActionOwner()->PlayAnimMontage(_aniMontage);
	}

	_shiftDirection = GetActionOwner()->GetVelocity().IsNearlyZero() ?
		GetActionOwner()->GetActorForwardVector() : GetActionOwner()->GetVelocity().GetSafeNormal();

	GetActionOwner()->SetActorRotation(_shiftDirection.Rotation());
}

void UActionDodge::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	GetActionOwner()->AddMovementInput(_shiftDirection, _dodgeSpeed * deltaTime);
}


void UActionDodge::OnAnimMontageFinished(UAnimMontage* montage,bool interrupted)
{
	if(montage != _aniMontage)return;

	GetActionOwner()->GetMesh()->GetAnimInstance()->OnMontageBlendingOut.RemoveDynamic(this, &UActionDodge::OnAnimMontageFinished);
	SetProcessSucceed();
}