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
