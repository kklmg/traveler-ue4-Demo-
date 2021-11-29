// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/Projectile.h"
#include "TeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API ATeleportProjectile : public AProjectile
{
	GENERATED_BODY()
public:
	ATeleportProjectile();
	virtual void VExecuteSpecialAction() final;

private:
	UPROPERTY(EditDefaultsOnly)
	FVector	_TeleportOffset;
};
