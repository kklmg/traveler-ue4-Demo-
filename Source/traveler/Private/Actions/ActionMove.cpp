// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMove.h"
#include "Character/MyCharacter.h"
#include "Components/AttributeComponent.h"


UActionMove::UActionMove() 
{
	_actionName = TEXT("Move");
}

void UActionMove::VBegin(AActor* actor, UActionData* actionData)
{
}

void UActionMove::VUpdate(float deltaTime, AActor* actor, UActionData* actionData)
{
	//Get My Character
	AMyCharacter* pCharacter = Cast<AMyCharacter>(actor);
	check(pCharacter != nullptr);

	//Get Attribute
	UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	check(pAttributeComponent != nullptr);

	pCharacter->AddMovementInput(actionData->Direction, pAttributeComponent->GetVelocity() * deltaTime);

	SetState(EActionState::AS_FINISHED);
}