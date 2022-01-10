// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/ThrowerData.h"
#include "ThrowerDataProviderInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UThrowerDataProviderInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IThrowerDataProviderInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FThrowerData VGetThrowerData() PURE_VIRTUAL(UThrowerDataProviderInterface::VGetThrowerData, return FThrowerData(););
};
