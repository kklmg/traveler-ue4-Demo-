// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TeleportProjectile.h"
#include "Character/CreatureCharacter.h"
#include "Components/ActionComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"



ATeleportProjectile::ATeleportProjectile() 
{
	_TeleportOffset = FVector(250, 0, 1000);
}

void ATeleportProjectile::VExecuteSpecialAction() 
{
	if (!GetInstigator()) return;

	UActionComponent* actionComp = 
		Cast<UActionComponent>(GetInstigator()->GetComponentByClass(UActionComponent::StaticClass()));

	if (actionComp)
	{
		FVector TeleportLocation = GetActorLocation() + GetActorForwardVector() * _TeleportOffset.X + FVector(0, 0, _TeleportOffset.Z);

		actionComp->GetActionBlackBoard()->WriteData_FVector(EActionDataKey::EACTD_TeleportLocation, TeleportLocation);
		actionComp->ExecuteAction(EActionType::EACT_Teleport);
		//creatureCharacter->LaunchCharacter(GetVelocity(), true, true);
		Destroy();
	}
}

