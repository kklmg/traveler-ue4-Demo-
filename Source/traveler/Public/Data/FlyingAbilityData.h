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
	float YawAngSpeedMax;
	UPROPERTY(EditDefaultsOnly)
	float YawAcc;
	UPROPERTY(EditDefaultsOnly)
	float PitchAngSpeed;
	UPROPERTY(EditDefaultsOnly)
	float PitchLimit;
	UPROPERTY(EditDefaultsOnly)
	float RollAngSpeed;
	UPROPERTY(EditDefaultsOnly)
	float RollLimit;
};
