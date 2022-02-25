// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimulatorBase.generated.h"

DECLARE_DELEGATE_OneParam(FSimulationSignal, float);

/**
 * 
 */

USTRUCT(BlueprintType)
struct FProcessSection
{
	GENERATED_USTRUCT_BODY()
public:
	FSimulationSignal OnStartDelegate;
	FSimulationSignal OnTickDelegate;
	FSimulationSignal OnEndDelegate;

	float durationTime;
};



UCLASS(Blueprintable)
class TRAVELER_API USimulatorBase : public UObject
{
	GENERATED_BODY()
public:
	USimulatorBase();

	void Tick(float deltaTime);

private:
	float _sectionProcessElapsedTime;
	float _totalProcessElapsedTime;

	int32 curProcessIndex;

	UPROPERTY()
	TArray<FProcessSection> _processSections;
};
