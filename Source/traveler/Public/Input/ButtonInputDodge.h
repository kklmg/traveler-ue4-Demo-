// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputActionBase.h"
#include "ButtonInputDodge.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputDodge : public UButtonInputActionBase
{
	GENERATED_BODY()
public:
	UButtonInputDodge();
protected:
	void VTMPress() override;
	void VTMPressing(float deltaTime) override;
	void VTMRelease() override;
};
