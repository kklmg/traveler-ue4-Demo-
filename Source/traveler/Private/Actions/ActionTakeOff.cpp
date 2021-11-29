// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionTakeOff.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UActionTakeOff::UActionTakeOff()
{
	_actionName = ActionName::TAKEOFF;
}

void UActionTakeOff::VExecute()
{
	Super::VExecute();

	_actionOwner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UActionTakeOff::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}