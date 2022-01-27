// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputActionBase.h"
#include "ButtonInputSprint.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputSprint : public UButtonInputActionBase
{
	GENERATED_BODY()

public:
	UButtonInputSprint();
protected:	
	void VTMPress() override;
	void VTMPressing(float deltaTime) override;
	void VTMRelease() override;

};
