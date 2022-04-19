// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FlyingAbilityData.generated.h"

/**
 * 
 */
USTRUCT()
struct TRAVELER_API FFlyingAbilityData 
{
	GENERATED_BODY()

public:
	FFlyingAbilityData();

	UPROPERTY(EditDefaultsOnly)
	float YawRate;
	UPROPERTY(EditDefaultsOnly)
	float PitchLimit;
	UPROPERTY(EditDefaultsOnly)
	float RollLimit;
	UPROPERTY(EditDefaultsOnly)
	float SpeedXYMax;
	UPROPERTY(EditDefaultsOnly)
	float SpeedZMax;
	UPROPERTY(EditDefaultsOnly)
	float AccelXY;
	UPROPERTY(EditDefaultsOnly)
	float AccelZ;
};
