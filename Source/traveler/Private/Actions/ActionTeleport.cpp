// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionTeleport.h"
#include "GameFramework/Character.h"

UActionTeleport::UActionTeleport()
{
	_actionName = ActionName::TELEPORT;
	_actionType = EActionType::EACT_Teleport;
}

void UActionTeleport::VExecute()
{
	Super::VExecute();

	FVector location;
	if (_actionData->TryReadVectorData(ActionData::TeleportLocation, location)) 
	{
		_actionOwner->SetActorLocation(location);
	}
}

void UActionTeleport::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}