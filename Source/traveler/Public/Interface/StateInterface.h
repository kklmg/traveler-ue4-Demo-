// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/StateData.h"
#include "StateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual FStateData VGetStateData() PURE_VIRTUAL(IStateInterface::VGetStateData, return FStateData(););
	
	virtual void VSetSituationState(ESituationState newState) PURE_VIRTUAL (IStateInterface::VSetSituationState,);
	virtual void VSetActionState(EActionState newState) PURE_VIRTUAL (IStateInterface::VSetActionState,);
	virtual void VSetHealthState(EHealthState newState) PURE_VIRTUAL (IStateInterface::VSetHealthState,);
	virtual void VSetPostureState(EPostureState newState) PURE_VIRTUAL (IStateInterface::VSetPostureState,);

	virtual FOnSituationStateChanged* VGetSituationStateChangedDelegate() PURE_VIRTUAL(IStateInterface::VGetSituationStateChangedDelegate, return nullptr;);
	virtual FOnActionStateChanged* VGetActionStateChangedDelegate() PURE_VIRTUAL(IStateInterface::VGetActionStateChangedDelegate, return nullptr;);
	virtual FOnHealthStateChanged* VGetHealthStateChangedDelegate() PURE_VIRTUAL(IStateInterface::VGetHealthStateChangedDelegate, return nullptr;);
	virtual FOnPostureStateChanged* VGetPostureStateChangedDelegate() PURE_VIRTUAL(IStateInterface::VGetPostureStateChangedDelegate, return nullptr;);
};
