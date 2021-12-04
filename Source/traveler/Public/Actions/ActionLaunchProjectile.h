// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "ActionLaunchProjectile.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class TRAVELER_API UActionLaunchProjectile : public UAction
{
	GENERATED_BODY()
	
public:
	UActionLaunchProjectile();

	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = projectileClass)
	TSubclassOf<AProjectile> projectileClass;

	UPROPERTY()
	TArray<AProjectile*> arrayProjectiles;
};
