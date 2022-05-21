// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ViewModelBase.h"
#include "MyMacros.h"
#include "AnimationModelBase.generated.h"

/**
 * 
 */

namespace NSAnimationDataKey
{	
	//bool
	DECLARE_CONST_FNAME(bIsSprinting)
	DECLARE_CONST_FNAME(bWantToJump)
	DECLARE_CONST_FNAME(bIsAlive)

	//float
	DECLARE_CONST_FNAME(fMaxSpeed)
	DECLARE_CONST_FNAME(fWalkingSpeed)
	DECLARE_CONST_FNAME(fSprintingSpeed)
	DECLARE_CONST_FNAME(fCameraPitch)
	DECLARE_CONST_FNAME(fCameraPitchMax)
	DECLARE_CONST_FNAME(fCameraPitchMin)

	//vector
	DECLARE_CONST_FNAME(vMovingDirection)
	DECLARE_CONST_FNAME(vPendingInput)
	DECLARE_CONST_FNAME(vMovingVelocity)

	//byte
	DECLARE_CONST_FNAME(byteMovementMode)

	//object
	DECLARE_CONST_FNAME(objWeapon)
	DECLARE_CONST_FNAME(objFootIKData)
};


UCLASS(BlueprintType)
class TRAVELER_API UAnimationModelBase : public UViewModelBase
{
	GENERATED_BODY()

};