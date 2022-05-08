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

	void OnPressed();
	void OnPressing(float deltaTime);
	void OnReleased();
protected:
	virtual void VTMOnPressed();
	virtual void VTMOnPressing(float deltaTime);
	virtual void VTMOnReleased();

private:
	float _pressingTime;
	bool _isPressing;
};
