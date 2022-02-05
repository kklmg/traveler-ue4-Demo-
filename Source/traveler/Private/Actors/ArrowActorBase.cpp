// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ArrowActorBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

AArrowActorBase::AArrowActorBase()
{
	_timeToDrop = 5.0f;
	_arrowState = EArrowState::EAS_Spawned;
	_gravity = 0.1f;
	_lifeAfterLaunch = 30.0f;
}

void AArrowActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AArrowActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_arrowState == EArrowState::EAS_Launched)
	{
		_elapsedTimeFromLaunch += DeltaTime;
	}

	if (_timeToDrop > _elapsedTimeFromLaunch)
	{
		_projectileMovementComp->ProjectileGravityScale = _gravity;
	}
}

void AArrowActorBase::Launch()
{
	_arrowState = EArrowState::EAS_Launched;
}

void AArrowActorBase::SetLaunchDirection(FVector dir)
{
	_launchDirection = dir;
}
