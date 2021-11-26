// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionJump.h"
#include "Character/MyCharacter.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


UActionJump::UActionJump() 
{
	_actionName = ActionName::JUMP;
}

void UActionJump::VExecute()
{
	Super::VExecute();

	//Get My Character
	AMyCharacter* character = Cast<AMyCharacter>(_actionOwner);
	check(character != nullptr);

	//Get Attribute
	UAttributeComponent* pAttributeComponent = character->GetAttributeComponent();
	check(pAttributeComponent != nullptr);

	//character->LandedDelegate
	character->MovementModeChangedDelegate.AddDynamic(this, &UActionJump::OnMovementModeChanged);

	character->Jump();
	if (_aniMontage != nullptr)
	{
		character->PlayAnimMontage(_aniMontage);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("playing jumping animation"));
	}
}

void UActionJump::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}


void UActionJump::OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	if (/*PrevMovementMode ==  && */Character->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		//Get My Character
		Character->StopJumping();

		if (_aniMontage != nullptr)
		{
			Character->StopAnimMontage(_aniMontage);
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("landed"));
		Character->MovementModeChangedDelegate.RemoveDynamic(this, &UActionJump::OnMovementModeChanged);
	}
}