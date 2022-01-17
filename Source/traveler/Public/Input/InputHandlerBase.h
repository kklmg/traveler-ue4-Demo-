// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumInputType.h"
#include "InputHandlerBase.generated.h"

class UButtonInputBase;

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
	void HandleButtonPress(EInputType inputType);
	UFUNCTION()
	void HandleButtonRelease(EInputType inputType);

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UButtonInputBase>> _buttonClasses;

	UPROPERTY()
	TMap<EInputType,UButtonInputBase*> _mapButtons;
};
