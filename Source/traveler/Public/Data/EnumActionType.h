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
	EACT_Throw UMETA(DisplayName = "Throw"),
	EACT_Ascend UMETA(DisplayName = "Ascend"),
};

UENUM(BlueprintType)
enum class EActionData : uint8
{
	EACTD_None UMETA(DisplayName = "None"),
	EACTD_TeleportLocation UMETA(DisplayName = " TeleportLocation"),
	EACTD_MovementInput UMETA(DisplayName = "MovementInput"),
	EACTD_Peojectile_SpawnedLocation UMETA(DisplayName = "Peojectile_SpawnedLocation"),
	EACTD_Peojectile_FlyingDirection UMETA(DisplayName = "Peojectile_FlyingDirection"),
	EACTD_Peojectile_FlyingSpeed UMETA(DisplayName = "Peojectile_FlyingSpeed"),
	EACTD_DestLocation UMETA(DisplayName = "DestLocation"),
};


class TRAVELER_API EnumActionType
{
public:
	EnumActionType();
	~EnumActionType();
};