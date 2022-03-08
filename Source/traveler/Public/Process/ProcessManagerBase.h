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
	void ExecuteProcess(IProcessInterface* process);

	void ExecutePresetedProcess(FName processName);
	void StopProcess(FName processName);
	void StopAllProcess();

	void AddToProcessPresets(IProcessInterface* process);


	bool IsProcessRunning(FName processName);

	void Tick(float deltaTime);

private:
	UPROPERTY()
	TMap<FName, TScriptInterface<IProcessInterface>> _runningProcesses;
	UPROPERTY()
	TMap<FName, TScriptInterface<IProcessInterface>> _processPresets;
};
