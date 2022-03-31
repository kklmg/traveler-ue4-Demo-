// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameSystem/EventBroker.h"
#include "AnimationCommunicatorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UAnimationCommunicatorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IAnimationCommunicatorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual void VPublishEvent(FName eventName, UEventDataBase* eventData) PURE_VIRTUAL(IAnimationCommunicatorInterface::VPublishEvent, );
	virtual bool VTryGetEventDelegate(FName eventName, FOnEventPublished& outDelegate) PURE_VIRTUAL(IAnimationCommunicatorInterface::VTryGetEventDelegate, return false;);
};
