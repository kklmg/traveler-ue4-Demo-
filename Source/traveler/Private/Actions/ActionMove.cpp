// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMove.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/Character.h"


UActionMove::UActionMove() 
{
	_actionName = ActionName::MOVE;
	_actionType = EActionType::EACT_Moving;
}

void UActionMove::VExecute()
{
	Super::VExecute();

	_actionOwner->AddMovementInput(_actionData->GetMovementInput());
}

void UActionMove::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

	//Get Attribute
	//UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	//check(pAttributeComponent != nullptr);
}