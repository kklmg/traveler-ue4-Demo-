// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponProcess/BowProcess/BowProcessBase.h"
#include "BowProcessFire.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UBowProcessFire : public UBowProcessBase
{
	GENERATED_BODY()

public:
	UBowProcessFire();

	virtual bool VCanExecute() override;
	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;

	virtual void VTMOnDead() override;
};
