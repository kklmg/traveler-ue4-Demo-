// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMove.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"


UActionMove::UActionMove() 
{
	_actionName = ActionName::MOVE;
	_actionType = EActionType::EACT_Moving;
}

void UActionMove::VTMExecute()
{
	FVector out_MovementInput;
	bool out_bTurnToMovingDirection = true;


	if (GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_MovementInput, out_MovementInput))
	{
		GetActionBlackBoard()->TryGetData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, out_bTurnToMovingDirection);

		//rotation
		if(out_bTurnToMovingDirection)
		{
			GetActionOwner()->SetActorRotation(out_MovementInput.Rotation());
		}
		
		//translation
		GetActionOwner()->AddMovementInput(out_MovementInput);
	}
}

void UActionMove::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}