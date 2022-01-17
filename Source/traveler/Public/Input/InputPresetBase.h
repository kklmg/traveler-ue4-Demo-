// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputPresetBase.generated.h"

class UButtonInputBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UInputPresetBase : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UButtonInputBase>> _buttonClasses;
};
