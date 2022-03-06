// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "WeaponProcessBase.generated.h"

class AWeaponBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UWeaponProcessBase : public UProcessBase
{
	GENERATED_BODY()

public:
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;

	virtual void VSetWeapon(AWeaponBase* weapon);

	float GetElapsedTime();

private:
	float _elapsedTime;

	UPROPERTY()
	AWeaponBase* _weapon;
};
