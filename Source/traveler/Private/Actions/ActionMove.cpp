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

void UActionMove::VExecute()
{
	Super::VExecute();

	FVector outMovementInput;

	if(_actionBlackBoard->TryGetData_FVector(EActionData::EACTD_MovementInput, outMovementInput))
	{
		_actionOwner->AddMovementInput(outMovementInput);
	}
}

void UActionMove::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

	//Get Attribute
	//UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	//check(pAttributeComponent != nullptr);
}