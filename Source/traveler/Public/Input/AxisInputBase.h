// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputBase.h"
#include "AxisInputBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UAxisInputBase : public UInputBase
{
	GENERATED_BODY()
public:
	virtual void VHandleInputAxis(float value);
};