// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damage/DamageData.h"
#include "DamageHandlerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageHandlerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IDamageHandlerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void VHandleDamage(float basicDamage, EElementalType damageType, FVector impactPoint, AActor* causer, APawn* instigator) PURE_VIRTUAL(IDamageHandlerInterface::VHandleDamage, );
	virtual void VHandleDamageData(UDamageData* damageData, FVector impactPoint, AActor* causer, APawn* instigator) PURE_VIRTUAL(IDamageHandlerInterface::VHandleDamage, );
	virtual void VHandleStatusEffect(UStatusEffectData* statusEffectData, FVector impactPoint, AActor* causer, APawn* instigator) PURE_VIRTUAL(IDamageHandlerInterface::VHandleStatusEffect, );
};
