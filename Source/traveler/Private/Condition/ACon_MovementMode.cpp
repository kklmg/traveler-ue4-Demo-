// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ACon_MovementMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/DebugMessageHelper.h"

void UACon_MovementMode::VSetActor(AActor* actor)
{
	Super::VSetActor(actor);

	_character = Cast<ACharacter>(actor);
	_character->MovementModeChangedDelegate.AddDynamic(this, &UACon_MovementMode::OnMovementModeChanged);
}

void UACon_MovementMode::SetValidateData(EMovementMode movementMode)
{
	_movementMode = movementMode;
}

bool UACon_MovementMode::VTMValidate()
{
	if (!Super::VTMValidate()) return false;
	return _character ? _character->GetCharacterMovement()->MovementMode == _movementMode : false;
}

void UACon_MovementMode::OnMovementModeChanged(ACharacter* character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Validate();
}