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

namespace InputActionName
{
	const FName MOVEFORWARD = FName(TEXT("MoveForward"));
	const FName MOVERIGHT = FName(TEXT("MoveRight"));
	const FName JUMP = FName(TEXT("Jump"));
	const FName SPRINT = FName(TEXT("Sprint"));
	const FName DODGE = FName(TEXT("Dodge"));
	const FName FIRE = FName(TEXT("Fire"));
	const FName AIM = FName(TEXT("Aim"));
	const FName ASCEND = FName(TEXT("ascend"));
	const FName DESCEND = FName(TEXT("descend"));
	const FName Action1 = FName(TEXT("Action1"));
	const FName Action2 = FName(TEXT("Action2"));
	const FName Action3 = FName(TEXT("Action3"));
	const FName Action4 = FName(TEXT("Action4"));
	const FName CAMERAPITCH = FName(TEXT("CameraPitch"));
	const FName CAMERAYAW = FName(TEXT("CameraYaw"));
	const FName CAMERAZOOMINOUT = FName(TEXT("CameraZoomInOut"));
}