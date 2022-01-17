// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EInputType : uint8
{
	EIT_None UMETA(DisplayName = "None"),
	EIT_Forward UMETA(DisplayName = "Forward"),
	EIT_Right UMETA(DisplayName = "Right"),
	EIT_Jump UMETA(DisplayName = "Jump"),
	EIT_Sprint UMETA(DisplayName = "Sprint"),
	EIT_Dodge UMETA(DisplayName = "Dodge"),
	EIT_Fire UMETA(DisplayName = "Fire"),
	EIT_Aim UMETA(DisplayName = "Aim"),
	EIT_CameraPitch UMETA(DisplayName = "CameraPitch"),
	EIT_CameraYaw UMETA(DisplayName = "CameraYaw"),
	EIT_CameraZoomInOut UMETA(DisplayName = "CameraZoomInOut"),
};


