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
	void Init();
	bool Execute();
	bool Abort();
	bool IsAlive();
	bool IsDead();
	bool IsInstantProcess();
	FName GetProcessName();

	UFUNCTION(BlueprintCallable)
	EProcessState GetProcessState();

	void Tick(float deltaTime);
public:
	virtual bool VCanExecute();
	
protected:	
	virtual void VTMInit();
	virtual void VTMExecute();
	virtual void VTMTick(float deltaTime);

	virtual void VTMOnDead();
	virtual void VTMOnSucceed();
	virtual void VTMOnFailed();
	virtual void VTMOnAborted();

protected:
	bool SetProcessSucceed();
	bool SetProcessFailed();
	bool SetProcessAborted();

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
