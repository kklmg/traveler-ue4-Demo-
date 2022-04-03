// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Event/EventDataBase.h"
#include "EventBrokerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UEventBrokerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IEventBrokerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual void VPublishEvent(FName eventName, UEventDataBase* eventData) PURE_VIRTUAL(IAnimationCommunicatorInterface::VPublishEvent, );

	virtual FOnEventPublished& VGetEventDelegate(FName eventName) PURE_VIRTUAL(IAnimationCommunicatorInterface::VGetEventDelegate, return _tempEventPublished;);
private:
	FOnEventPublished _tempEventPublished;
};