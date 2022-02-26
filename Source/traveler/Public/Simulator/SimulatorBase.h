// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessSectionBase.h"
#include "SimulatorBase.generated.h"

DECLARE_DELEGATE_OneParam(FSimulationSignal, float);

/**
 * 
 */


UCLASS(Blueprintable)
class TRAVELER_API USimulatorBase : public UObject
{
	GENERATED_BODY()
public:
	USimulatorBase();

	void Tick(float deltaTime);

private:
	float _elapsedTime;

	int32 curProcessIndex;

	UPROPERTY()
	TArray<UProcessSectionBase*> _processSections;
};
