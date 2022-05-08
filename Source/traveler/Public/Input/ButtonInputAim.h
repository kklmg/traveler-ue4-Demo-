// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "ButtonInputAim.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputAim : public UButtonInputBase
{
	GENERATED_BODY()
public:
	UButtonInputAim();
protected:
	void VTMOnPressed() override;
	void VTMOnPressing(float deltaTime) override;
	void VTMOnReleased() override;
};
