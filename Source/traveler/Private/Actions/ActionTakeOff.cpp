// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionTakeOff.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UActionTakeOff::UActionTakeOff()
{
	_actionName = ActionName::TAKEOFF;
	_actionType = EActionType::EACT_TakeOff;
}

void UActionTakeOff::VTMExecute()
{
	GetActionOwner()->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UActionTakeOff::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}