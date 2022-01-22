// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputActionBase.h"
#include "ButtonInputActionSimple.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputActionSimple : public UButtonInputActionBase
{
	GENERATED_BODY()
public:
	virtual void VPress() override;
	//virtual void VPressing(float deltaTime) override;
	//virtual void VRelease() override;
};
