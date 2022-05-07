// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "ButtonInputDelegate.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputDelegate : public UButtonInputBase
{
	GENERATED_BODY()
public:

	UButtonInputDelegate();
public:
	FButtonInputSignature OnButtonPressed;
	FButtonInputSignature OnButtonPressing;
	FButtonInputSignature OnButtonReleased;

protected:
	virtual void VTMPress();
	virtual void VTMPressing(float deltaTime);
	virtual void VTMRelease();
};
