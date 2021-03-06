// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETransformType : uint8
{
	ETransform_None UMETA(DisplayName = "None"),
	ETransform_LeftHand UMETA(DisplayName = "LeftHand"),
	ETransform_RightHand UMETA(DisplayName = "RightHand"),

	ETransform_Mouth UMETA(DisplayName = "Mouth"),
	ETransform_Head UMETA(DisplayName = "Head"),
	ETransform_LeftFoot UMETA(DisplayName = "LeftFoot"),
	ETransform_RightFoot UMETA(DisplayName = "RightFoot"), 
	ETransform_Ground UMETA(DisplayName = "Ground"),

	ETransform_Muzzle UMETA(DisplayName = "Muzzle"),
	ETransform_BowString UMETA(DisplayName = "BowString"),
	ETransform_LeftHandDraw UMETA(DisplayName = "LeftHandDraw"),
	ETransform_RightHandDraw UMETA(DisplayName = "RightHandDraw"),

	ETransform_StatusUI UMETA(DisplayName = "StatusUI"),
};