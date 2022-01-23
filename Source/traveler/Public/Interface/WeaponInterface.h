// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon/Weapon.h"
#include "WeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IWeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void VEquipWeapon(AWeapon* weapon)PURE_VIRTUAL (UWeaponInterface::VSetDamage, );
	virtual AWeapon* VGetEquipedWeapon()PURE_VIRTUAL (UWeaponInterface::VGetEquipedWeapon,return nullptr; );
};
