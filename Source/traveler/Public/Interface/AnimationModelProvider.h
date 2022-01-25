// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/AnimationModel.h"
#include "AnimationModelProvider.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UAnimationModelProvider : public UInterface
{
	GENERATED_BODY()
};

static FAnimationModel temp;
/**
 * 
 */
class TRAVELER_API IAnimationModelProvider
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual FAnimationModel& VGetAnimationModel() PURE_VIRTUAL(IAnimationModelProvider::VGetAnimationModel, return temp;);
};
