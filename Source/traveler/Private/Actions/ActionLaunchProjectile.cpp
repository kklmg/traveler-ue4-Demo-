// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionLaunchProjectile.h"
#include "Projectile/Projectile.h"


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


	_actionData->TryReadVectorData(ActionData::Projectile_SpawnLocation, spawnLocation);
	_actionData->TryReadVectorData(ActionData::Projectile_Direction, flyDirection);
	_actionData->TryReadFloatData(ActionData::Projectile_Direction, speed);

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