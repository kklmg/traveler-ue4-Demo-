// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AnimationModelBase.h"
#include "AnimationModel_Player.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TRAVELER_API UAnimationModel_Player : public UAnimationModelBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* WalkingSpeed;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* SprintSpeed;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* NormalizedSpeed;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* NormalizedSpeed_IdleWalk;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* NormalizedSpeed_WalkSprint;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Vector* PendingInput;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Vector* MovingVelocity;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Bool* bIsSprinting;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Bool* bWantToJump;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* CameraPitch;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* CameraPitchMax;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* CameraPitchMin;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* CameraPitchNormal;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* LeftFootOffset;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Float* RightFootOffset;

	UPROPERTY(BlueprintReadWrite)
	UReactive_Bool* bTakeOutWeapon;


	//UPROPERTY(BlueprintReadWrite)
	//AWeaponBase* weapon;

		//UPROPERTY(BlueprintReadWrite)
	//	TEnumAsByte<enum EMovementMode> MovementMode;
};
