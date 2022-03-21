// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	EATT_Level UMETA(DisplayName = "Level"),
	EATT_Health UMETA(DisplayName = "Health"),
	EATT_Mana UMETA(DisplayName = "Mana"),
	EATT_Stamina UMETA(DisplayName = "Stamina"),
	EATT_Energy UMETA(DisplayName = "Energy"),
	EATT_Strength UMETA(DisplayName = "Strength"),
	EATT_Defence UMETA(DisplayName = "Defence"),
	EATT_WalkingSpeed UMETA(DisplayName = "WalkingSpeed"),
	EATT_SprintingSpeed UMETA(DisplayName = "SprintingSpeed"),
	EATT_FlyingSpeed UMETA(DisplayName = "FlyingSpeed"),
};


class TRAVELER_API EnumAttributeType
{
public:
	EnumAttributeType();
	~EnumAttributeType();
};
