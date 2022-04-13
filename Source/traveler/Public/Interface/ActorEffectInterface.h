// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/CombatData.h"
#include "Effet/EnumEffect.h"
#include "ActorEffectInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActorEffectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IActorEffectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void VPlayEffect(EEffectType effectType, uint8 effectOption) PURE_VIRTUAL(IActorEffectInterface::VPlayEffect, );
	virtual void VStopEffect(EEffectType effectType, uint8 effectOption) PURE_VIRTUAL(IActorEffectInterface::VStopEffect, );
};
