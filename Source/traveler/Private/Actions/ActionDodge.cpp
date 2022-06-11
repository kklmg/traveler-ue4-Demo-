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
	_animMontageType = EAnimMontageKey::EAnimMontage_Dodge;
	_bIsInstantProcess = false;
	_dodgeForce = 2000000;

	GetCostData()->AddCost(EStatusType::EStatus_Stamina,20);
}


bool UActionDodge::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	EMovementMode movementMode = GetActionOwner()->GetCharacterMovement()->MovementMode;
	bool bIsWalking = (movementMode == EMovementMode::MOVE_Walking || movementMode == EMovementMode::MOVE_NavWalking);

	return bIsWalking && GetActionComp()->IsActionAlive(EActionType::EACT_Jumping) == false;
}

void UActionDodge::VOnExecute()
{
	Super::VOnExecute();

	GetActionComp()->AbortAction(EActionType::EACT_Aim);
	GetActionComp()->AbortAction(EActionType::EACT_Fire);

	FVector normalizedVelocity = GetActionOwner()->GetCharacterMovement()->Velocity.GetSafeNormal();
	normalizedVelocity.Z = 0;
	_shiftDirection = normalizedVelocity.IsNearlyZero() ? GetActionOwner()->GetActorForwardVector() : normalizedVelocity;

	GetActionOwner()->SetActorRotation(normalizedVelocity.Rotation());
}

void UActionDodge::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	GetActionOwner()->GetCharacterMovement()->AddForce(_shiftDirection * _dodgeForce);
	//GetActionOwner()->GetCharacterMovement()->Mass
}