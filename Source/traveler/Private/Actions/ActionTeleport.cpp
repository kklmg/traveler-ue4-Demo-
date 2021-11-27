// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionTeleport.h"
#include "Character/MyCharacter.h"

UActionTeleport::UActionTeleport()
{
	_actionName = ActionName::TELEPORT;
}

void UActionTeleport::VExecute()
{
	Super::VExecute();

	FVector location;
	if (_actionData->TryReadVectorData(ActionKey::TeleportLocation, location)) 
	{
		_actionOwner->SetActorLocation(location);
	}
}

void UActionTeleport::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}