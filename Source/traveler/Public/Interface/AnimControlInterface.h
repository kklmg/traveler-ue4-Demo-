// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/AnimationModelBase.h"
#include "Data/StateData.h"
#include "AnimControlInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UAnimControlInterface : public UInterface
{
	GENERATED_BODY()
};

//
/**
 * 
 */
class TRAVELER_API IAnimControlInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//animation Model
	UFUNCTION(BlueprintCallable)
	virtual UAnimationModelBase* VGetAnimationModel() PURE_VIRTUAL(IAnimationModelProvider::VGetAnimationModel, return nullptr;);

	//animation State
	UFUNCTION(BlueprintCallable)
	virtual void VSetAnimationState(EAnimationState newState) PURE_VIRTUAL(IAnimControlInterface::VSetAnimationState, );
	UFUNCTION(BlueprintCallable)
	virtual EAnimationState VGetAnimationState() PURE_VIRTUAL(IAnimControlInterface::VGetAnimationState, return EAnimationState::EAnimState_None;);
	virtual FOnAnimationStateChanged& VGetAnimationStateChangedDelegate() PURE_VIRTUAL(IAnimControlInterface::VGetAnimationStateChangedDelegate, return _tempAnimationStateChanged;);

private:
	
	FOnAnimationStateChanged _tempAnimationStateChanged;
};