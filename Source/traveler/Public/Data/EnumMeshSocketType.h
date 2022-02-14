// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMeshSocketType : uint8
{
	MST_None UMETA(DisplayName = "None"),
	MST_LeftHand UMETA(DisplayName = "LeftHand"),
	MST_RightHand UMETA(DisplayName = "RightHand"),
	MST_LeftHandDraw UMETA(DisplayName = "LeftHandDraw"),
	MST_RightHandDraw UMETA(DisplayName = "RightHandDraw"),
	MST_Mouth UMETA(DisplayName = "Mouth"),
	MST_Head UMETA(DisplayName = "Head"),
	MST_LeftFoot UMETA(DisplayName = "LeftFoot"),
	MST_RightFoot UMETA(DisplayName = "RightFoot"),
	MST_Muzzle UMETA(DisplayName = "Muzzle"),
	MST_BowString UMETA(DisplayName = "BowString"),
};