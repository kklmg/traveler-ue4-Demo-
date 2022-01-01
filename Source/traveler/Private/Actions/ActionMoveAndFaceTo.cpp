// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionMoveAndFaceTo.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"

UActionMoveAndFaceTo::UActionMoveAndFaceTo() 
{
	_actionName = ActionName::MOVE;
	_actionType = EActionType::EACT_Moving;
}
void UActionMoveAndFaceTo::VExecute()
{
	Super::VExecute();

	FVector outMovementInput;

	if (_actionBlackBoard->TryGetData_FVector(EActionData::EACTD_MovementInput, outMovementInput))
	{
		_actionOwner->SetActorRotation(outMovementInput.Rotation());
		_actionOwner->AddMovementInput(outMovementInput);
	}

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
