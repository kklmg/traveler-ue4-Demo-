// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionTeleport.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"

UActionTeleport::UActionTeleport()
{
	_processName = NSNameAction::TELEPORT;
	_actionType = EActionType::EACT_Teleport;
}

void UActionTeleport::VTMExecute()
{
	FVector outLocation;
	if (GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_TeleportLocation, outLocation)) 
	{
		GetActionOwner()->SetActorLocation(outLocation);
	}
}

void UActionTeleport::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}