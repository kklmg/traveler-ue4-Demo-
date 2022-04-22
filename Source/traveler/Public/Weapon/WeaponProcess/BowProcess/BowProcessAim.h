// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponProcess/BowProcess/BowProcessBase.h"
#include "BowProcessAim.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UBowProcessAim : public UBowProcessBase
{
	GENERATED_BODY()
public:
	UBowProcessAim();
	
	virtual bool VTMCanExecute() override;
	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;

	virtual void VTMOnDead() override;
};
