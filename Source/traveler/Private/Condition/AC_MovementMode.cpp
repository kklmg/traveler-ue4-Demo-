// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/AC_MovementMode.h"
#include "Event/ActorEventDataBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UAC_MovementMode::VValidate(UEventDataBase* eventData)
{
	UActorEventDataBase* actorEventData = Cast<UActorEventDataBase>(eventData);
	if (!actorEventData)return false;


	ACharacter* character = Cast<ACharacter>(actorEventData->GetActor());
	if (!character) return false;

	return (character->GetCharacterMovement()->MovementMode == _movementMode);
}

TArray<FName> UAC_MovementMode::VGetReactiveEventNames()
{
	TArray<FName> events;
	events.Add(NEventNames::MovementModeChanged);
	return events;
}

void UAC_MovementMode::SetValidateData(EMovementMode movementMode)
{
	_movementMode = movementMode;
}
