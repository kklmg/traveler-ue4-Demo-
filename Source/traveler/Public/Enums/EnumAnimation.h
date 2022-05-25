// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumAnimation.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class EAnimationState : uint8
{
	EAnimState_None UMETA(DisplayName = "None"),
	EAnimState_Walk UMETA(DisplayName = "Walk"),
	EAnimState_Sprint UMETA(DisplayName = "Sprint"),
	EAnimState_Jump UMETA(DisplayName = "Jump"),
	EAnimState_Fall UMETA(DisplayName = "Fall"),
	EAnimState_Land UMETA(DisplayName = " Land"),
};

UENUM(BlueprintType)
enum class EAnimMontageKey : uint8
{
	EAnimMontage_None UMETA(DisplayName = "None"),
	EAnimMontage_Throw UMETA(DisplayName = "Throw"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnimationStateChanged, EAnimationState, prevState, EAnimationState, newState);