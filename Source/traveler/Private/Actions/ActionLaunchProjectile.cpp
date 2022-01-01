// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionLaunchProjectile.h"
#include "Projectile/Projectile.h"
#include "Actions/ActionData/ActionBlackBoard.h"


UActionLaunchProjectile::UActionLaunchProjectile()
{
	_actionName = ActionName::ProjectileAttack;
	_actionType = EActionType::EACT_LaunchProjectile;
}

void UActionLaunchProjectile::VExecute()
{
	Super::VExecute();


	FVector spawnLocation, flyDirection;
	float speed = 0.0f;


	_actionBlackBoard->TryGetData_FVector(EActionData::EACTD_Peojectile_SpawnedLocation, spawnLocation);
	_actionBlackBoard->TryGetData_FVector(EActionData::EACTD_Peojectile_FlyingDirection, flyDirection);
	_actionBlackBoard->TryGetData_Float(EActionData::EACTD_Peojectile_FlyingSpeed, speed);

	if (projectileClass != nullptr) 
	{
		AProjectile* projectile = NewObject<AProjectile>(this, projectileClass);
		projectile->SetActorLocation(spawnLocation);
		projectile->SetFlyingDirection(flyDirection);
		projectile->Launch(speed);

		if (projectile != nullptr)
		{
			arrayProjectiles.Add(projectile);
		}
	}

	SetActionState(EActionState::AS_SUCCEEDED);

};




void UActionLaunchProjectile::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}