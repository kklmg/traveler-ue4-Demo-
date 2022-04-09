// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/AC_MovementMode.h"
#include "Event/ActorEventDataBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/DebugMessageHelper.h"

bool UAC_MovementMode::VValidate(UEventDataBase* eventData)
{
	if(!eventData)
	{
		UDebugMessageHelper::Messsage_String("eventData is NUll", "");
		return false;
	}

	UActorEventDataBase* actorEventData = Cast<UActorEventDataBase>(eventData);
	if (!actorEventData) 
	{
		UDebugMessageHelper::Messsage_String("eventData cast failed", "");
		return false;
	}

	ACharacter* character = Cast<ACharacter>(actorEventData->GetActor());
	if (!character) return false;

	return (character->GetCharacterMovement()->MovementMode == _movementMode);
}

void UAC_MovementMode::SetValidateData(EMovementMode movementMode)
{
	_movementMode = movementMode;
}
