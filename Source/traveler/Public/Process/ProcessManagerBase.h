// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Process/ProcessInterface.h"
#include "ProcessManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UProcessManagerBase : public UObject
{
	GENERATED_BODY()
public:
	void ExecuteProcess(FName processName);
	void StopProcess(FName processName);
	void StopAllProcess();

	void AddProcess(IProcessInterface* process);

	EProcessState GetProcessState(FName processName);

	void Tick(float deltaTime);

private:
	TMap<FName,IProcessInterface*> _runningProcesses;
	TMap<FName, IProcessInterface*> _processesStorage;
};
