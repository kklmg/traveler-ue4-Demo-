// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/EnumProcessState.h"
#include "ProcessInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProcessInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IProcessInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void VEnter()  PURE_VIRTUAL(IProcessInterface::VEnter, );
	virtual void VTick(float deltaTime) PURE_VIRTUAL(IProcessInterface::VTick, );
	virtual void VEnd() PURE_VIRTUAL(IProcessInterface::VEnd, );
	virtual void VReset() PURE_VIRTUAL(IProcessInterface::VReset, );
	virtual bool VIsAlive() PURE_VIRTUAL(IProcessInterface::VIsAlive, return false; );
	virtual bool VIsDead() PURE_VIRTUAL(IProcessInterface::VIsDead, return true;);

	virtual EProcessState VGetProcessState() PURE_VIRTUAL(IProcessInterface::VGetProcessState, return EProcessState::EPS_None;);
	virtual void VSetState(EProcessState newState)PURE_VIRTUAL(IProcessInterface::VSetState, );
};
