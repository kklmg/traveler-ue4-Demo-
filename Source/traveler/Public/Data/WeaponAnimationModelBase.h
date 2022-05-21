// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AnimationModelBase.h"
#include "Enums/EnumWeaponType.h"
#include "MyMacros.h"
#include "WeaponAnimationModelBase.generated.h"

/**
 * 
 */

namespace NSNameAnimData
{
	DECLARE_CONST_FNAME(bIsFiring)
	DECLARE_CONST_FNAME(bIsAiming)
	DECLARE_CONST_FNAME(fWristRoll)
	DECLARE_CONST_FNAME(bArrowsSpawned)
	DECLARE_CONST_FNAME(bDrawingBow)
	DECLARE_CONST_FNAME(byteBowState)
}

UCLASS(BlueprintType)
class TRAVELER_API UWeaponAnimationModelBase : public UAnimationModelBase
{
	GENERATED_BODY()
public:
	EWeaponType WeaponType;
};
