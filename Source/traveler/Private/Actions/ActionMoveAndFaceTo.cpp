// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMoveAndFaceTo.h"
#include "Character/MyCharacter.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UActionMoveAndFaceTo::UActionMoveAndFaceTo() 
{
	_actionName = TEXT("MoveAndFaceTo");
}
void UActionMoveAndFaceTo::VBegin(AActor* actor, UActionData* actionData)
{
	//Get My Character
	AMyCharacter* character = Cast<AMyCharacter>(actor);
	check(character != nullptr);

	//Get Attribute
	UAttributeComponent* pAttributeComponent = character->GetAttributeComponent();
	check(pAttributeComponent != nullptr);


	/*if (_AniMontage != nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("playing walking animation"))
		character->PlayAnimMontage(_AniMontage);
		GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Red, TEXT("playing walking animation"));
	}*/
}

void UActionMoveAndFaceTo::VUpdate(float deltaTime, AActor* actor, UActionData* actionData)
{
	//Get My Character
	AMyCharacter* pCharacter = Cast<AMyCharacter>(actor);
	check(pCharacter != nullptr);

	//Get Attribute
	UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	check(pAttributeComponent != nullptr);

	pCharacter->SetActorRotation(actionData->Direction.Rotation());


	pCharacter->AddMovementInput(actionData->Direction);

	SetState(EActionState::AS_FINISHED);
}
