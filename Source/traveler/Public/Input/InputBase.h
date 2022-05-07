// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Input/InputPresetBase.h"
#include "Enums/EnumActionType.h"
#include "InputBase.generated.h"


/**
 * 
 */
UCLASS()
class TRAVELER_API UInputBase : public UObject
{
	GENERATED_BODY()

public:
	UInputBase();

	void Init(UInputPresetBase* inputPreset);

	void SetBindingName(FName bindingName);
	FName GetBindingName();

protected:
	UInputPresetBase* GetInputPreset();

	UPROPERTY(EditDefaultsOnly)
	FName _bindingName;
private:
	UPROPERTY()
	UInputPresetBase* _inputPrest;

	friend class UInputPresetBase;
};
