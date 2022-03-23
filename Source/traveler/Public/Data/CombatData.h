// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatData.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	EDamage_None UMETA(DisplayName = "None"),
	EDamage_Physics UMETA(DisplayName = "Physics"),
	EDamage_Fire UMETA(DisplayName = "Fire"),
	EDamage_Water UMETA(DisplayName = "Water"),
	EDamage_Ice UMETA(DisplayName = "Ice"),
	EDamage_Electricity UMETA(DisplayName = "Electricity"),
	EDamage_Poison UMETA(DisplayName = "Poison"),
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
};

