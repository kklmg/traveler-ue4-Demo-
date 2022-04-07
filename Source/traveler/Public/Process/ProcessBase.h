// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Process/ProcessInterface.h"
#include "ProcessBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessStateChanged, EProcessState);

/**
 * 
 */
UCLASS()
class TRAVELER_API UProcessBase : public UObject, public IProcessInterface
{
	GENERATED_BODY()
public:
	virtual void VInitialize() final;
	virtual bool VExecute() final;
	virtual void VTick(float deltaTime) final;
	virtual void VAbort() final;
	virtual void VReset() final;

	virtual bool VIsAlive() final;
	virtual bool VIsDead() final;
	virtual EProcessState VGetProcessState() final;
	virtual bool VSetProcessState(EProcessState newState) final;

	//virtual FName VGetProcessName();
	virtual bool VCanExecute() final;
	virtual bool VIsInstantProcess() override;

protected:	

	virtual void VTMInitialize();
	virtual bool VTMCanExecute();
	virtual void VTMExecute();
	virtual void VTMTick(float deltaTime);
	virtual void VTMReset();

	virtual void VTMOnDead();
	virtual void VTMOnSucceed();
	virtual void VTMOnFailed();
	virtual void VTMOnAborted();

	void SetSucceed();
	void SetFailed();

private:
	EProcessState _processState;

public:
	FOnProcessStateChanged OnProcessStateChanged;
};
