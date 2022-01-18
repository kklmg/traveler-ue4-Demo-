// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumInputType.h"
#include "InputHandlerBase.generated.h"

class UButtonInputBase;
class UAxisInputBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UInputHandlerBase : public UObject
{
	GENERATED_BODY()

public:
	void Initialize();

	UFUNCTION()
	void HandleAxisInput(EInputType inputType, float value);
	UFUNCTION()
	void HandleButtonPress(FName actionName);
	UFUNCTION()
	void HandleButtonRelease(FName actionName);

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UAxisInputBase>> _axisClasses;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UButtonInputBase>> _buttonClasses;

	UPROPERTY()
	TMap<EInputType, UAxisInputBase*> _mapAxis;

	UPROPERTY()
	TMap<FName,UButtonInputBase*> _mapButtons;
};
