// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterAttribute.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, float, PreviousValue, float, NewValue);

namespace AttributeName 
{
	const FName Health = FName(TEXT("Health"));
	const FName Mana = FName(TEXT("Mana"));
	const FName Energy = FName(TEXT("Energy"));
	const FName WalkingSpeed = FName(TEXT("WalkingSpeed"));
	const FName RuningSpeed = FName(TEXT("RuningSpeed"));
	const FName FlyingSpeed = FName(TEXT("FlyingSpeed"));
	const FName Level = FName(TEXT("Level"));
	const FName Strength = FName(TEXT("Strength"));
}

/**
 * 
 */
UCLASS()
class TRAVELER_API UCharacterAttribute : public UObject
{
	GENERATED_BODY()
public:
	UCharacterAttribute();

	void Initialize(FName attributeName, float minValue, float maxValue, float value);

	UFUNCTION(BlueprintCallable)
	void SetValue(float newValue);
	UFUNCTION(BlueprintCallable)
	void ApplyValueChange(float deltaValue);

	UFUNCTION(BlueprintCallable)
	float GetValue();
	UFUNCTION(BlueprintCallable)
	float GetMinValue();
	UFUNCTION(BlueprintCallable)
	float GetMaxValue();
	UFUNCTION(BlueprintCallable)
	float GetPreviousValue();
	UFUNCTION(BlueprintCallable)
	FName GetName();

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged onValueChanged;

private:
	UPROPERTY(EditDefaultsOnly)
	FName _AttributeName;

	UPROPERTY(EditDefaultsOnly)
	float _minValue;

	UPROPERTY(EditDefaultsOnly)
	float _maxValue;

	UPROPERTY(EditDefaultsOnly)
	float _currentValue;

	float _previousValue;
};