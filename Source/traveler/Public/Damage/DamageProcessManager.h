// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessManagerBase.h"
#include "DamageProcessManager.generated.h"

class UDamageProcessBase;
/**
 * 
 */
UCLASS()
class TRAVELER_API UDamageProcessManager : public UObject
{
	GENERATED_BODY()
public:
	UDamageProcessManager();

	void ExecuteProcess(UDamageProcessBase* process);

	void Tick(float deltaTime);

private:
	UPROPERTY()
	TArray<UDamageProcessBase*> _runningProcesses;
	UPROPERTY()
	TArray<uint32> _emptyIndicies;

	UPROPERTY(EditDefaultsOnly)
	uint32 _poolSize;
};
