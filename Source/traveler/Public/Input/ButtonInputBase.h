// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Input/InputBindingNames.h"
#include "Input/InputBase.h"
#include "ButtonInputBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyInput, Log, All);

DECLARE_DELEGATE_OneParam(FButtonInputSignature, UButtonInputBase*);

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputBase : public UInputBase
{
	GENERATED_BODY()
public:

	UButtonInputBase();

public:
	float GetPressingTime();
	bool IsPressing();

	void Press();
	void Pressing(float deltaTime);
	void Release();
protected:
	virtual void VOnPressed();
	virtual void VOnPressing(float deltaTime);
	virtual void VOnReleased();

private:
	float _pressingTime;
	bool _isPressing;
};
