// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumInputType.h"
#include "ButtonInputBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyInput, Log, All);

DECLARE_DELEGATE_OneParam(FButtonInputSignature, UButtonInputBase*);

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputBase : public UObject
{
	GENERATED_BODY()
public:

	UButtonInputBase();
public:
	FButtonInputSignature OnButtonPressed;
	FButtonInputSignature OnButtonReleased;

public:
	virtual void VPress();
	virtual void VPressing(float deltaTime);
	virtual void VRelease();

	FName GetInputMappingName();
	float GetHoldingTime();
	bool IsPressing();

private:
	UPROPERTY(EditDefaultsOnly)
	FString _buttonName;
	FName _inputMappingName;

	float _holdingTime;
	bool _isPressing;
};
