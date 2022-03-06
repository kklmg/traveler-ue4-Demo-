// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponProcess/WeaponProcessBase.h"
#include "Weapon/BowBase.h"
#include "BowProcessBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UBowProcessBase : public UWeaponProcessBase
{
	GENERATED_BODY()

public:
	virtual void VSetWeapon(AWeaponBase* weapon) override;

protected:
	UPROPERTY()
	 ABowBase* _bow;
};
