// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputActionBase.h"
#include "ButtonInputAim.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputAim : public UButtonInputActionBase
{
	GENERATED_BODY()
	
protected:
	void VTMPress() override;
	void VTMPressing(float deltaTime) override;
	void VTMRelease() override;
};
