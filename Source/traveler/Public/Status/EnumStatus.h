// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

//UENUM(BlueprintType)
//enum class EBasicStatus : uint8
//{
//	EBasicStatus_Health UMETA(DisplayName = "Health"),
//	EBasicStatus_Mana UMETA(DisplayName = "Mana"),
//	EBasicStatus_Stamina UMETA(DisplayName = "Stamina"),
//	EBasicStatus_Energy UMETA(DisplayName = "Energy"),
//};


UENUM(BlueprintType)
enum class EStatusType : uint8
{
	EStatus_Health UMETA(DisplayName = "Health"),
	EStatus_Mana UMETA(DisplayName = "Mana"),
	EStatus_Stamina UMETA(DisplayName = "Stamina"),
	EStatus_Energy UMETA(DisplayName = "Energy"),
	EStatus_Strength UMETA(DisplayName = "Strength"),
	EStatus_Defence UMETA(DisplayName = "Defence"),
	EStatus_WalkingSpeed UMETA(DisplayName = "WalkingSpeed"),
	EStatus_SprintingSpeed UMETA(DisplayName = "SprintingSpeed"),
	EStatus_FlyingSpeed UMETA(DisplayName = "FlyingSpeed"),
};
