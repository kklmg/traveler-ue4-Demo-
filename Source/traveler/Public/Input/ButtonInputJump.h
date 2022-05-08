// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "ButtonInputJump.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputJump : public UButtonInputBase
{
	GENERATED_BODY()
	
public:
	UButtonInputJump();
protected:
	void VTMOnPressed() override;
	void VTMOnPressing(float deltaTime) override;
	void VTMOnReleased() override;
};
