// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ThrowableInterface.generated.h"

class UCurveFloat;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UThrowableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class TRAVELER_API IThrowableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void VSetDamage(float damage) PURE_VIRTUAL(UThrowableInterface::VSetDamage, );
	virtual void VSetVelocity(FVector velocity) PURE_VIRTUAL(UThrowableInterface::VSetVelocity,);
	virtual void VSetLife(float life) PURE_VIRTUAL(UThrowableInterface::VSetLife, );
	virtual void VSetScale(float scale) PURE_VIRTUAL(UThrowableInterface::VSetScale, );
	virtual void VSetScaleCurve(UCurveFloat* curve) PURE_VIRTUAL(UThrowableInterface::VSetScaleCurve, );
};
