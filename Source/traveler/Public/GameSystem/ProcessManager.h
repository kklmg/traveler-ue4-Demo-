// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Process.h"
#include "ProcessManager.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UProcessManager : public UObject
{
	GENERATED_BODY()

private:
	TArray<UProcess*> _processList;

public:
	// construction
	UProcessManager();

	
	unsigned int UpdateProcesses(unsigned long deltaMs);  // updates all attached processes
	void AddProcess(UProcess* pProcess);  // add a process to the process list
	void AbortAllProcesses();

	// accessors
	int32 GetProcessCount(void) const;
private:
	void ClearAllProcesses(void); 
};
