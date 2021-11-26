// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMove.h"
#include "Character/MyCharacter.h"
#include "Components/AttributeComponent.h"


UActionMove::UActionMove() 
{
	_actionName = ActionName::MOVE;
}

void UActionMove::VExecute()
{
	Super::VExecute();

	_actionOwner->AddMovementInput(_actionData->Direction);
}

void UActionMove::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

	//Get Attribute
	//UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	//check(pAttributeComponent != nullptr);
}