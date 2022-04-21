// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumCombat.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class EElementalType : uint8
{
	EElemental_None UMETA(DisplayName = "None"),
	EElemental_Physics UMETA(DisplayName = "Physics"),
	EElemental_Fire UMETA(DisplayName = "Fire"),
	EElemental_Water UMETA(DisplayName = "Water"),
	EElemental_Ice UMETA(DisplayName = "Ice"),
	EElemental_Electricity UMETA(DisplayName = "Electricity"),
	EElemental_Poison UMETA(DisplayName = "Poison"),
	
	EElemental_Size UMETA(Hidden),
};

UENUM(BlueprintType)
enum class EStatusEffect : uint8
{
	EStatusEffect_NONE UMETA(Hidden),
	EStatusEffect_Fire UMETA(DisplayName = "Fire"),
	EStatusEffect_Water UMETA(DisplayName = "Water"),
	EStatusEffect_Ice UMETA(DisplayName = "Ice"),
	EStatusEffect_Electricity UMETA(DisplayName = "Electricity"),
	EStatusEffect_Poison UMETA(DisplayName = "Poison"),
	EStatusEffect_Stun UMETA(DisplayName = "Stun"),

	EStatusEffect_Size UMETA(Hidden),
};

