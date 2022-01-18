// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumInputType.h"
#include "AxisInputBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UAxisInputBase : public UObject
{
	GENERATED_BODY()

public:
	UAxisInputBase();

public:
	void Tick(float deltaTime);
	virtual void VHandleInput(float value);

	EInputType GetInputType();

private:
	UPROPERTY(EditDefaultsOnly)
	EInputType _inputType;

	UPROPERTY(EditDefaultsOnly)
	FString _axisName;

};
