// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMove.h"
#include "Components/AttributeComponent.h"
#include "Components/ActionComponent.h"
#include "Interface/StateInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Data/CostData.h"
#include "Interface/AttributeInterface.h"


UActionMove::UActionMove() 
{
	_actionName = ActionName::MOVE;
	_actionType = EActionType::EACT_Moving;

	_sprintCost = CreateDefaultSubobject<UCostData>(TEXT("SprintCost"));
	_sprintCost->SetCost(EAttributeType::EATT_Stamina, 0.25f);
}

bool UActionMove::VTMCanExecute()
{
	EMovementMode movementMode = GetActionOwner()->GetCharacterMovement()->MovementMode;
	//bool bIsWalking = movementMode == EMovementMode::MOVE_Walking || movementMode == EMovementMode::MOVE_NavWalking;
	bool bIsDodging = GetActionComponent()->CheckActionIsInProgress(EActionType::EACT_Dodge);

	return/* bIsWalking && */(!bIsDodging);
}

void UActionMove::VTMExecute()
{
	FVector out_MovementInput;
	bool out_bTurnToMovingDirection = true;
	bool out_bWantToSprint = false;


	if (GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_MovementInput, out_MovementInput))
	{
		GetActionBlackBoard()->TryGetData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, out_bTurnToMovingDirection);

		//rotation
		if(out_bTurnToMovingDirection)
		{
			GetActionOwner()->SetActorRotation(out_MovementInput.Rotation());
		}

		GetActionBlackBoard()->TryGetData_Bool(EActionDataKey::EACTD_WantToSprint, out_bWantToSprint);
		if(out_bWantToSprint && _attributeInterface)
		{
			if(_attributeInterface->VTryConsume(_sprintCost))
			{
			}
			else
			{
				GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_WantToSprint, false);
			}
		}
		
		//translation
		GetActionOwner()->AddMovementInput(out_MovementInput);
	}
}

void UActionMove::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}