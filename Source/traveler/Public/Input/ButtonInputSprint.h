// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "ButtonInputSprint.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputSprint : public UButtonInputBase
{
	GENERATED_BODY()

public:
	UButtonInputSprint();
protected:	
	void VOnPressed() override;
	void VOnPressing(float deltaTime) override;
	void VOnReleased() override;
};
