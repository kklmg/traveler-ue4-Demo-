// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "AnimationModel.generated.h"


USTRUCT(BlueprintType)
struct FAnimationModel
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float WalkingSpeed;
	UPROPERTY(BlueprintReadWrite)
	float SprintSpeed;
	UPROPERTY(BlueprintReadWrite)
	float NormalizedSpeed;
	UPROPERTY(BlueprintReadWrite)
	float NormalizedSpeed_IdleWalk;
	UPROPERTY(BlueprintReadWrite)
	float NormalizedSpeed_WalkSprint;
	UPROPERTY(BlueprintReadWrite)
	FVector PendingInput;


	UPROPERTY(BlueprintReadWrite)
	FVector MovingVelocity;
	UPROPERTY(BlueprintReadWrite)
	bool bIsSprinting;


	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<enum EMovementMode> MovementMode;
	UPROPERTY(BlueprintReadWrite)
	bool bWantToJump;


	UPROPERTY(BlueprintReadWrite)
	float CameraPitch;
	UPROPERTY(BlueprintReadWrite)
	float CameraPitchMax;
	UPROPERTY(BlueprintReadWrite)
	float CameraPitchMin;
	UPROPERTY(BlueprintReadWrite)
	float CameraPitchNormal;
	UPROPERTY(BlueprintReadWrite)
	float LeftFootOffset;
	UPROPERTY(BlueprintReadWrite)
	float RightFootOffset;
	


	UPROPERTY(BlueprintReadWrite)
	bool bIsWeaponFiring;
	UPROPERTY(BlueprintReadWrite)
	bool bIsWeaponAiming;
	UPROPERTY(BlueprintReadWrite)
	bool bTakeOutWeapon;
	UPROPERTY(BlueprintReadWrite)
	AWeaponBase* weapon;
};