// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionTakeOff.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UActionTakeOff::UActionTakeOff()
{
	_processName = NSNameAction::TAKEOFF;
	_actionType = EActionType::EACT_TakeOff;
}

void UActionTakeOff::VOnExecute()
{
	GetActionOwner()->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UActionTakeOff::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);
}