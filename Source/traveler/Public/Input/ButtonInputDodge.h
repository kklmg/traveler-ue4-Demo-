// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "ButtonInputDodge.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputDodge : public UButtonInputBase
{
	GENERATED_BODY()
public:
	UButtonInputDodge();
protected:
	void VTMOnPressed() override;
	void VTMOnPressing(float deltaTime) override;
	void VTMOnReleased() override;
};
