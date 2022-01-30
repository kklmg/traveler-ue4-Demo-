// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionTeleport.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"

UActionTeleport::UActionTeleport()
{
	_actionName = ActionName::TELEPORT;
	_actionType = EActionType::EACT_Teleport;
}

void UActionTeleport::VExecute()
{
	Super::VExecute();

	FVector outLocation;
	if (_actionBlackBoard->TryGetData_FVector(EActionDataKey::EACTD_TeleportLocation, outLocation)) 
	{
		_actionOwner->SetActorLocation(outLocation);
	}
}

void UActionTeleport::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}