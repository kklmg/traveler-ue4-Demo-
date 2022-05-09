// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "Actions/ActionBase.h"
#include "WeaponActionBase.generated.h"

class AWeaponBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UWeaponActionBase : public UActionBase
{
	GENERATED_BODY()

public:
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;

	virtual void VSetWeapon(AWeaponBase* weapon);

private:
	UPROPERTY()
	AWeaponBase* _weapon;
};
