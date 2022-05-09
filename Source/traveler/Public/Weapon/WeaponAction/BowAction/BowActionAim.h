// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponAction/BowAction/BowActionBase.h"
#include "BowActionAim.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UBowActionAim : public UBowActionBase
{
	GENERATED_BODY()
public:
	UBowActionAim();
	
	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;

	virtual void VTMOnDead() override;
};
