// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ObjectData.h"
#include "MyMacros.h"

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
	EACT_FaceTo UMETA(DisplayName = "FaceTo"),
	EACT_TakeOff UMETA(DisplayName = "TakeOff"),
	EACT_Teleport UMETA(DisplayName = "Teleport"),
	EACT_Throw UMETA(DisplayName = "Throw"),
	EACT_Ascend UMETA(DisplayName = "Ascend"),
	EACT_Fire UMETA(DisplayName = "Fire"),
	EACT_Aim UMETA(DisplayName = "Aim"),
	EACT_Guard UMETA(DisplayName = "Guard"),
	EACT_Shoot UMETA(DisplayName = "Shoot"),
	EACT_Max UMETA(DisplayName = "Max"),
};

namespace NSActionData
{
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(WantToSprint, UDataBool)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(FaceToDest, UDataBool)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(BrakeAtDest, UDataBool)


	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(MovementInput, UDataVector)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(RotationCenter, UDataVector)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(TeleportLocation, UDataVector)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(DestLocation, UDataVector)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(TrackCenter, UDataVector)	
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(FaceToDirection, UDataVector)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(ShootingDirection, UDataVector)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(ShootingTargetLocation, UDataVector)


	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(DestAltitude, UDataFloat)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(DestRadius, UDataFloat)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(keepDistanceXY, UDataFloat)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(keepDistance_Ver, UDataFloat)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(NormalizedSpeed, UDataFloat)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(DashDistance, UDataFloat)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(TrackRadius, UDataFloat)
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(ShootingSpeed, UDataFloat)

	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(FaceToActor, AActor)
};






UENUM(BlueprintType)
enum class EActionPrestGroup : uint8
{
	EACTPresetGroup_None UMETA(DisplayName = "None"),
	EACTPresetGroup_BasicActions UMETA(DisplayName = "BasicActions"),
	EACTPresetGroup_WeaponActions UMETA(DisplayName = "WeaponActions"),
};