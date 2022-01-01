// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TeleportProjectile.h"
#include "Character/CreatureCharacter.h"
#include "Actions/Action.h"
#include "Actions/ActionData/ActionBlackBoard.h"



ATeleportProjectile::ATeleportProjectile() 
{
	_TeleportOffset = FVector(250, 0, 1000);
}

void ATeleportProjectile::VExecuteSpecialAction() 
{
	ACreatureCharacter* creatureCharacter = GetInstigator<ACreatureCharacter>();
	if (creatureCharacter != nullptr) 
	{
		FVector TeleportLocation = GetActorLocation() + GetActorForwardVector() * _TeleportOffset.X + FVector(0, 0, _TeleportOffset.Z);

		creatureCharacter->GetActionBlackBoard()->WriteData_FVector(EActionData::EACTD_TeleportLocation, TeleportLocation);
		creatureCharacter->ExecuteAction(EActionType::EACT_Teleport);
		//creatureCharacter->LaunchCharacter(GetVelocity(), true, true);
		Destroy();
	}
}

