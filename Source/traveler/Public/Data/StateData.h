// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateData.generated.h"

UENUM(BlueprintType)
enum class ESituationState : uint8
{
	ESS_None UMETA(DisplayName = "None"),
	ESS_OnGround UMETA(DisplayName = "OnGround"),
	ESS_OnWall UMETA(DisplayName = "OnWall"),
	ESS_InAir UMETA(DisplayName = "InAir"),
	ESS_InWater UMETA(DisplayName = "InWater"),
	ESS_UnderWater UMETA(DisplayName = "UnderWater"),
	ESS_Riding UMETA(DisplayName = "Riding"),
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_None UMETA(DisplayName = "None"),
	EAS_Idle UMETA(DisplayName = "Idle"),
	EAS_Moving UMETA(DisplayName = "Moving"),
	EAS_Sprinting UMETA(DisplayName = "Sprinting"),
	EAS_Dodging UMETA(DisplayName = "Dodging"),
	EAS_Falling UMETA(DisplayName = "Falling"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_Aiming UMETA(DisplayName = "Aiming"),
	EAS_BeHitted UMETA(DisplayName = "beHitted"),
};

UENUM(BlueprintType)
enum class EHealthState : uint8
{
	EHS_None UMETA(DisplayName = "None"),
	EHS_Healthy UMETA(DisplayName = "Healthy"),
	EHS_LowHealth UMETA(DisplayName = "LowHealth"),
	EHS_NoHealth UMETA(DisplayName = "NoHealth"),
};

UENUM(BlueprintType)
enum class EPostureState : uint8
{
	EPS_None UMETA(DisplayName = "None"),
	EPS_UpRight UMETA(DisplayName = "UpRight"),
	EPS_Crouch UMETA(DisplayName = "Crouch"),
	EPS_Crawl UMETA(DisplayName = "Crawl"),
};

UENUM(BlueprintType)
enum class EAnimationState : uint8
{
	E_AnimState_None UMETA(DisplayName = "None"),
	E_AnimState_Ground UMETA(DisplayName = "Ground"),
	E_AnimState_Jump UMETA(DisplayName = "Jump"),
	E_AnimState_Fall UMETA(DisplayName = "Fall"),
	E_AnimState_Land UMETA(DisplayName = " Land"),
};



USTRUCT(BlueprintType)
struct FStateData
{
	GENERATED_USTRUCT_BODY()

public:
	FStateData();

	UPROPERTY(BlueprintReadWrite)
	ESituationState SituationState;

	UPROPERTY(BlueprintReadWrite)
	EActionState ActionState;
	
	UPROPERTY(BlueprintReadWrite)
	EAnimationState AnimationState;

	UPROPERTY(BlueprintReadWrite)
	EHealthState HealthState;
	
	UPROPERTY(BlueprintReadWrite)
	EPostureState PostureState;

	UPROPERTY(BlueprintReadWrite)
	FVector Velocity;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<enum EMovementMode> MovementMode;
};



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnimationStateChanged, EAnimationState, prevState, EAnimationState, newState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSituationStateChanged, ESituationState, SituationState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionStateChanged, EActionState, ActionState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthStateChanged, EHealthState, HealthState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostureStateChanged, EPostureState, PostureState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyStateChanged, FStateData, State);