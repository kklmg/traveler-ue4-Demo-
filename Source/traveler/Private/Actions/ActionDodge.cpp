// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionDodge.h"
#include "Character/CreatureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/CostData.h"
#include "Weapon/WeaponBase.h"
#include "Components/WeaponComponent.h"


UActionDodge::UActionDodge()
{
	_actionName = NSNameAction::DODGE;
	_actionType = EActionType::EACT_Dodge;
	_bInstantAction = false;
	_dodgeSpeed = 250;

	GetCostData()->AddCost(EStatusType::EStatus_Stamina,20);
	
}

void UActionDodge::VInitialize(ACharacter* owner, UActionComponent* actionComp, UActionBlackBoard* actionBlackBoard)
{
	Super::VInitialize(owner, actionComp, actionBlackBoard);
}

bool UActionDodge::VTMCanExecute()
{
	EMovementMode movementMode = GetActionOwner()->GetCharacterMovement()->MovementMode;
	bool bIsWalking = (movementMode == EMovementMode::MOVE_Walking || movementMode == EMovementMode::MOVE_NavWalking);

	return bIsWalking;
}

void UActionDodge::VTMExecute()
{
	UAnimInstance* animInstance = GetActionOwner()->GetMesh()->GetAnimInstance();

	if (GetWeaponComp())
	{
		GetWeaponComp()->StopWeaponProcess(NSNameWeaponProcess::AIM);
		GetWeaponComp()->StopWeaponProcess(NSNameWeaponProcess::FIRE);
	}


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

	SetActionProcessSucceed();
}