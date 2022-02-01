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
	FVector outMovementInput;

	if(GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_MovementInput, outMovementInput))
	{
		GetActionOwner()->AddMovementInput(outMovementInput);
	}
}

void UActionMove::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	//Get Attribute
	//UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	//check(pAttributeComponent != nullptr);
}