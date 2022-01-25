// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_None UMETA(DisplayName = "None"),
	EWT_Sword UMETA(DisplayName = "Sword"),
	EWT_DualSword UMETA(DisplayName = "DualSword"),
	EWT_Knife UMETA(DisplayName = "Knife"),
	EWT_Bow UMETA(DisplayName = "Bow"),
};


UENUM(BlueprintType)
enum class EBowState : uint8
{
	EBS_Normal UMETA(DisplayName = "Normal"),
	EBS_Drawing UMETA(DisplayName = "Drawing"),
	EBS_FullyDrawed UMETA(DisplayName = "FullyDrawed"),
	EBS_OverDrawing UMETA(DisplayName = "OverDrawing"),
	EBS_Released UMETA(DisplayName = "Released"),
};

