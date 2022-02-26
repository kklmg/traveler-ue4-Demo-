// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Process/ProcessInterface.h"
#include "ProcessBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UProcessBase : public UObject, public IProcessInterface
{
	GENERATED_BODY()
public:
	virtual void VEnter() final;
	virtual void VTick(float deltaTime) final;
	virtual void VEnd() final;
	virtual void VReset() final;

	virtual void VTMEnter();
	virtual void VTMTick(float deltaTime);
	virtual void VTMEnd();
	virtual void VTMReset();

	virtual bool VIsAlive() final;
	virtual bool VIsDead() final;
	virtual EProcessState VGetProcessState() final;
	virtual void VSetState(EProcessState newState) final;

protected:

private:
	EProcessState _processState;
};
