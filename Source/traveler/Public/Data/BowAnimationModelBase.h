// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/WeaponAnimationModelBase.h"
#include "BowAnimationModelBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBowAnimationModelBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	EBowState BowState;

	UPROPERTY(BlueprintReadWrite)
	bool bIsHoldingArrows;

	UPROPERTY(BlueprintReadWrite)
	float HandRoll;
};

//UCLASS()
//class TRAVELER_API UBowAnimationModelBase : public UWeaponAnimationModelBase
//{
//	GENERATED_BODY()
//};
