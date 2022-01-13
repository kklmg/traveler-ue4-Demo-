// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ThrowerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UThrowerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IThrowerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void VSetSpawningLocation(FVector location) PURE_VIRTUAL(UThrowerInterface::VSetSpawningLocation, );
	virtual void VSetSpawningActorScale(float scale) PURE_VIRTUAL(UThrowerInterface::VSetSpawningActorScale, );
	virtual void VSetThrowingDirection(FVector direction) PURE_VIRTUAL(UThrowerInterface::VSetThrowingDirection, );
	virtual void VSetSpeed(float speed) PURE_VIRTUAL(UThrowerInterface::VSetSpeed, );
	virtual void VSetLife(float life) PURE_VIRTUAL(UThrowerInterface::VSetLife, );
	virtual void VAutoDestroy() PURE_VIRTUAL(UThrowerInterface::VAutoDestroy, );
};
