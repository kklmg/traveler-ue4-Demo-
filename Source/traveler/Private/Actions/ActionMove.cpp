// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMove.h"
#include "Components/ActionComponent.h"
#include "Components/StatusComponent.h"
#include "GameFramework/Character.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Data/CostData.h"


UActionMove::UActionMove() 
{
	_processName = NSNameAction::move;
	_actionType = EActionType::EACT_Moving;

	_sprintCost = CreateDefaultSubobject<UCostData>(TEXT("SprintCost"));
	_sprintCost->AddCost(EStatusType::EStatus_Stamina, 0.25f);
}

bool UActionMove::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	bool bIsDodging = GetActionComp()->IsActionAlive(EActionType::EACT_Dodge);
	return (bIsDodging == false && GetActionBlackBoard()->TryGetData_FVector(NSActionData::MovementInput::Name, _movementInput, true));
}

void UActionMove::VOnExecute()
{
	auto myMovementComp = Cast<UMyCharacterMovementComponent>(GetActionOwner()->GetCharacterMovement());

	bool out_bTurnToMovingDirection = true;
	bool out_bWantToSprint = false;

	GetActionBlackBoard()->TryGetData_Bool(NSActionData::FaceToDest::Name, out_bTurnToMovingDirection);

	//apply rotation
	if (out_bTurnToMovingDirection)
	{
		//FQuat deltaQuat = FQuat::FindBetween(GetActionOwner()->GetActorForwardVector(), out_MovementInput);			
		//GetActionOwner()->AddActorWorldRotation(deltaQuat);
		GetActionOwner()->SetActorRotation(_movementInput.ToOrientationQuat());
	}

	GetActionBlackBoard()->TryGetData_Bool(NSActionData::WantToSprint::Name, out_bWantToSprint);

	if(myMovementComp && GetStatusComp())
	{
		if(out_bWantToSprint && GetStatusComp()->TryApplyCost(_sprintCost))
		{
			myMovementComp->ToggleSprint(true);
		}
		else
		{
			myMovementComp->ToggleSprint(false);
		}
	}

	//apply movement
	GetActionOwner()->AddMovementInput(_movementInput);
}

void UActionMove::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);
}