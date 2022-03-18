// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/ActorUIData.h"
#include "ActorUIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActorUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IActorUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void VShowActorUI(EActorUI UIType) PURE_VIRTUAL(IActorUIInterface::VShowActorUI,);
	virtual void VHideActorUI(EActorUI UIType) PURE_VIRTUAL(IActorUIInterface::VHideActorUI,);
	virtual void VShowActorStatusUI(EActorStatusUI StatusUIType, float duration) PURE_VIRTUAL(IActorUIInterface::VShowActorStatusUI,);
	virtual void VHideActorStatusUI(EActorStatusUI StatusUIType) PURE_VIRTUAL(IActorUIInterface::VHideActorStatusUI,);
};