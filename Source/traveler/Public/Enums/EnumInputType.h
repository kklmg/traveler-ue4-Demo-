// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMacros.h"
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

namespace NSInputBindingName
{
	//Axis
	DECLARE_CONST_FNAME(MoveForward)
	DECLARE_CONST_FNAME(MoveRight)
	DECLARE_CONST_FNAME(MoveUpward)
	DECLARE_CONST_FNAME(CameraYaw)
	DECLARE_CONST_FNAME(CameraPitch)
	DECLARE_CONST_FNAME(CameraZoomInOut)

	//Action
	DECLARE_CONST_FNAME(Jump)
	DECLARE_CONST_FNAME(Sprint)
	DECLARE_CONST_FNAME(Dodge)
	DECLARE_CONST_FNAME(Fire)
	DECLARE_CONST_FNAME(Aim)
	DECLARE_CONST_FNAME(ascend)
	DECLARE_CONST_FNAME(descend)
	DECLARE_CONST_FNAME(Action1)
	DECLARE_CONST_FNAME(Action2)
	DECLARE_CONST_FNAME(Action3)
	DECLARE_CONST_FNAME(Action4)
}