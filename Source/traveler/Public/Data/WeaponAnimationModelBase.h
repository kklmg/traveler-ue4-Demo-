// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AnimationModelBase.h"
#include "Enums/EnumWeaponType.h"
#include "WeaponAnimationModelBase.generated.h"

/**
 * 
 */

namespace WeaponAnimationDataKey
{
	const FName bIsFiring = FName(TEXT("bIsFiring"));
	const FName bIsAiming = FName(TEXT("bIsAiming"));
	const FName fWristRoll = FName(TEXT("fWristRoll"));
	const FName bArrowsSpawned = FName(TEXT("bArrowsSpawned"));
	const FName bIsDrawingBow = FName(TEXT("bDrawingBow"));
	const FName byteBowState = FName(TEXT("byteBowState"));
}

UCLASS(BlueprintType)
class TRAVELER_API UWeaponAnimationModelBase : public UAnimationModelBase
{
	GENERATED_BODY()
public:
	EWeaponType WeaponType;
};
