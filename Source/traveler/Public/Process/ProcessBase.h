// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/EnumProcessState.h"
#include "ProcessBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcessStateChanged, EProcessState);

/**
 * 
 */
UCLASS(BlueprintType)
class TRAVELER_API UProcessBase : public UObject
{
	GENERATED_BODY()
public:
	bool Init();
	bool Execute();
	bool Abort();

	bool CanExecute();
	bool IsAlive();
	bool IsDead();
	bool IsInstantProcess();
	FName GetProcessName();
	EProcessState GetProcessState();

	void Tick(float deltaTime);

protected:	

	//Internal  functions ---------------------------

	virtual bool VTMCanExecute();
	virtual void VTMInit();
	virtual void VTMExecute();
	virtual void VTMTick(float deltaTime);
	virtual void VTMReset();

	virtual void VTMOnDead();
	virtual void VTMOnSucceed();
	virtual void VTMOnFailed();
	virtual void VTMOnAborted();

protected:
	bool SetSucceed();
	bool SetFailed();
	bool SetAborted();

	UPROPERTY(EditDefaultsOnly)
	FName _processName;

	UPROPERTY(EditDefaultsOnly)
	bool _bIsInstantProcess;

private:
	bool SetProcessState(EProcessState newState);

	EProcessState _processState;

public:
	FOnProcessStateChanged ProcessStateChangedDelegate;
};
