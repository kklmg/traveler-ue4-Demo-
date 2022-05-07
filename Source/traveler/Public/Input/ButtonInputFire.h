// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "ButtonInputFire.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputFire : public UButtonInputBase
{
	GENERATED_BODY()
public:
	UButtonInputFire();
protected:
	void VTMPress() override;
	void VTMPressing(float deltaTime) override;
	void VTMRelease() override;
};
