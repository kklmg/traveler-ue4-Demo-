// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMoveAndFaceTo.h"
#include "Character/MyCharacter.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UActionMoveAndFaceTo::UActionMoveAndFaceTo() 
{
	_actionName = ActionName::MOVE;
}
void UActionMoveAndFaceTo::VExecute()
{
	Super::VExecute();

	//rotation
	_actionOwner->SetActorRotation(_actionData->Direction.Rotation());

	//Movement

	_actionOwner->AddMovementInput(_actionData->Direction);

	//Get Attribute
	//UAttributeComponent* pAttributeComponent = character->GetAttributeComponent();
	//check(pAttributeComponent != nullptr);


	/*if (_AniMontage != nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("playing walking animation"))
		character->PlayAnimMontage(_AniMontage);
		GEngine->AddOnScreenDebugMessage(-1,1.0f, FColor::Red, TEXT("playing walking animation"));
	}*/
}

void UActionMoveAndFaceTo::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}
