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
	void Press();
	void Pressing(float deltaTime);
	void Release();

	FName GetInputMappingName();
	float GetHoldingTime();
	bool IsPressing();

protected:
	virtual void VTMPress();
	virtual void VTMPressing(float deltaTime);
	virtual void VTMRelease();

	UPROPERTY(EditDefaultsOnly)
	FString _buttonName;
	UPROPERTY(EditDefaultsOnly)
	FName _inputMappingName;

	float _holdingTime;
	bool _isPressing;
};
