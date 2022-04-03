// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/AC_MovementMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UAC_MovementMode::VValidate()
{
	ACharacter* character = Cast<ACharacter>(GetActor());

	if (!character) return false;
	return (character->GetCharacterMovement()->MovementMode == _movementMode);
}

void UAC_MovementMode::SetValidateData(EMovementMode movementMode)
{
	_movementMode = movementMode;
}
