// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ViewModelBase.h"
#include "AnimationModelBase.generated.h"

/**
 * 
 */

namespace AnimationDataKey
{	
	//bool
	const FName bIsSprinting = FName(TEXT("bIsSprinting"));
	const FName bWantToJump = FName(TEXT("bWantToJump"));

	//float
	const FName fWalkingSpeed = FName(TEXT("fWalkingSpeed"));
	const FName fSprintingSpeed = FName(TEXT("fSprintingSpeed"));
	const FName fCameraPitch = FName(TEXT("fCameraPitch"));
	const FName fCameraPitchMax = FName(TEXT("fCameraPitchMax"));
	const FName fCameraPitchMin = FName(TEXT("fCameraPitchMin"));

	//vector
	const FName vMovingDirection = FName(TEXT("vMovingDirection"));
	const FName vPendingInput = FName(TEXT("vPendingInput"));
	const FName vMovingVelocity = FName(TEXT("vMovingVelocity"));

	//byte
	const FName byteMovementMode = FName(TEXT("byteMovementMode"));

	//object
	const FName objWeapon = FName(TEXT("objWeapon"));
	const FName objFootIKData = FName(TEXT("objFootIKData"));
};


UCLASS()
class TRAVELER_API UAnimationModelBase : public UViewModelBase
{
	GENERATED_BODY()

};