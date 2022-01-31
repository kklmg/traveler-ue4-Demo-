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
	FVector MovingVelocity;
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
	bool bTakeOutWeapon;
	UPROPERTY(BlueprintReadWrite)
	AWeaponBase* weapon;
	

};