// Fill out your copyright notice in the Description page of Project Settings.


#include"../MyCharacter.h"
#include"../AttributeComponent.h"
#include "ActionMoveAndFaceTo.h"

void UActionMoveAndFaceTo::VUpdate(float deltaTime, AActor* actor, UActionData* actionData)
{
	//Get My Character
	AMyCharacter* pCharacter = Cast<AMyCharacter>(actor);
	check(pCharacter != nullptr);

	//Get Attribute
	UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	check(pAttributeComponent != nullptr);

	pCharacter->SetActorRotation(actionData->Direction.Rotation());
	pCharacter->AddMovementInput(actionData->Direction, pAttributeComponent->GetVelocity() * deltaTime);

	SetState(EActionState::AS_FINISHED);
}
