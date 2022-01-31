// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMoveAndFaceTo.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Interface/AttributeInterface.h"

UActionMoveAndFaceTo::UActionMoveAndFaceTo()
{
	_actionName = ActionName::MOVE;
	_actionType = EActionType::EACT_Moving;
}
void UActionMoveAndFaceTo::VExecute()
{
	Super::VExecute();

	FVector outMovementInput;
	if (GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_MovementInput, outMovementInput))
	{
		GetActionOwner()->SetActorRotation(outMovementInput.Rotation());
		GetActionOwner()->AddMovementInput(outMovementInput);
	}
}

void UActionMoveAndFaceTo::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}
