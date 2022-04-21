// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProcessManagerBase.generated.h"

class UProcessBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UProcessManagerBase : public UObject
{
	GENERATED_BODY()
public:
	void ExecuteProcess(UProcessBase* process);

	void ExecutePresetedProcess(FName processName);
	void StopProcess(FName processName);
	void StopAllProcess();

	void AddToProcessPresets(UProcessBase* process);


	bool IsProcessRunning(FName processName);

	void Tick(float deltaTime);

private:
	UPROPERTY()
	TMap<FName, UProcessBase*> _runningProcesses;
	UPROPERTY()
	TMap<FName, UProcessBase*> _processPresets;
};
