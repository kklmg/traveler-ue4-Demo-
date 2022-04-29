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
	EACT_FlyAround UMETA(DisplayName = "FlyAround"),
	EACT_TakeOff UMETA(DisplayName = "TakeOff"),
	EACT_Teleport UMETA(DisplayName = "Teleport"),
	EACT_Throw UMETA(DisplayName = "Throw"),
	EACT_Ascend UMETA(DisplayName = "Ascend"),
	EACT_Fire UMETA(DisplayName = "Fire"),
	EACT_Aim UMETA(DisplayName = "Aim"),
	EACT_Max UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class EActionDataKey : uint8
{
	EACTD_None UMETA(DisplayName = "None"),
	EACTD_TeleportLocation UMETA(DisplayName = " TeleportLocation"),
	EACTD_MovementInput UMETA(DisplayName = "MovementInput"),
	EACTD_RotationCenter UMETA(DisplayName = "RotationCenter"),
	EACTD_NormalizedSpeed UMETA(DisplayName = "NormalizedSpeed"),
	EACTD_Peojectile_SpawnedLocation UMETA(DisplayName = "Peojectile_SpawnedLocation"),
	EACTD_Peojectile_FlyingDirection UMETA(DisplayName = "Peojectile_FlyingDirection"),
	EACTD_Peojectile_FlyingSpeed UMETA(DisplayName = "Peojectile_FlyingSpeed"),
	EACTD_DestLocation UMETA(DisplayName = "DestLocation"),
	EACTD_DestRadius UMETA(DisplayName = "DestRadius"),
	EACTD_DestAltitude UMETA(DisplayName = "DestAltitude"),
	EACTD_WantToSprint UMETA(DisplayName = "WantToSprint"),
	EACTD_TurnToMovingDirection UMETA(DisplayName = "TurnToMovingDirection"),
};

