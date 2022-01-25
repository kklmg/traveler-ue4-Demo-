// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationModel.generated.h"


USTRUCT(BlueprintType)
struct FAnimationModel
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FVector MovingVelocity;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<enum EMovementMode> MovementMode;
	UPROPERTY(BlueprintReadWrite)
	float CameraPitchMax;
	UPROPERTY(BlueprintReadWrite)
	float CameraPitchMin;
};