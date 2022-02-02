// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AnimationModelBase.h"
#include "Data/EnumWeaponType.h"
#include "WeaponAnimationModelBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UWeaponAnimationModelBase : public UAnimationModelBase
{
	GENERATED_BODY()
public:
	EWeaponType WeaponType;
};
