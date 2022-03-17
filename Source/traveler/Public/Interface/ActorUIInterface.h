// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UI/BillBoardWidget.h"
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
	virtual void VShowWidget(EActorUI widgeType) PURE_VIRTUAL(IActorUIInterface::VShowWidget,);
	virtual void VHideWidget(EActorUI widgeType) PURE_VIRTUAL(IActorUIInterface::VHideWidget,);
};