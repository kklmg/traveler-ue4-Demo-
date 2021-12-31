// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EActionType : uint8
{
	EACT_None UMETA(DisplayName = "None"),
	EACT_Moving UMETA(DisplayName = "Moving"),
	EACT_Idle UMETA(DisplayName = "Idle"),
	EACT_Jumping UMETA(DisplayName = "Jumping"),
	EACT_Sprint UMETA(DisplayName = "Sprint"),
	EACT_Dodge UMETA(DisplayName = "Dodge"),
	EACT_Aiming UMETA(DisplayName = "Aiming"),
	EACT_Flying UMETA(DisplayName = "Flying"),
	EACT_FlyTo UMETA(DisplayName = "FlyTo"),
	EACT_TakeOff UMETA(DisplayName = "TakeOff"),
	EACT_Teleport UMETA(DisplayName = "Teleport"),
	EACT_LaunchProjectile UMETA(DisplayName = "LaunchProjectile"),
	EACT_SpreadAttack UMETA(DisplayName = "SpreadAttack"),
	EACT_Ascend UMETA(DisplayName = "Ascend"),
};



class TRAVELER_API EnumActionType
{
public:
	EnumActionType();
	~EnumActionType();
};
