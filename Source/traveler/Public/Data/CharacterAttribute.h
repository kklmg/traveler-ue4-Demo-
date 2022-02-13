// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumAttributeType.h"
#include "CharacterAttribute.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, float, PreviousValue, float, NewValue);

struct FAttributeRow;

/**
 * 
 */
UCLASS()
class TRAVELER_API UCharacterAttribute : public UObject
{
	GENERATED_BODY()
public:
	UCharacterAttribute();

	void Initialize(FAttributeRow* attributeRow, int level = 0);
	void Initialize(EAttributeType attributeType, FText attributeText, float value, float growthRate = 1.0f);
	void Initialize(EAttributeType attributeType, FText attributeText, float value, float minValue, float maxValue, float growthRate = 1.0f);

	void Tick(float deltaTime);

	UFUNCTION(BlueprintCallable)
	void SetValue(float newValue);
	UFUNCTION(BlueprintCallable)
	void ApplyValueChange(float deltaValue);

	UFUNCTION(BlueprintPure)
	float GetValue();
	UFUNCTION(BlueprintPure)
	float GetMinValue();
	UFUNCTION(BlueprintPure)
	float GetMaxValue();
	UFUNCTION(BlueprintPure)
	float GetPercentage();

	UFUNCTION(BlueprintPure)
	float GetPreviousValue();

	UFUNCTION(BlueprintPure)
	EAttributeType GetAttributeType();

	UFUNCTION(BlueprintPure)
	FText GetText();

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged onValueChanged;

private:
	UPROPERTY(EditDefaultsOnly)
	EAttributeType _attributeType;

	UPROPERTY(EditDefaultsOnly)
	FText _attributeText;

	UPROPERTY(EditDefaultsOnly)
	float _minValue;

	UPROPERTY(EditDefaultsOnly)
	float _maxValue;

	UPROPERTY(EditDefaultsOnly)
	float _currentValue;

	UPROPERTY(EditDefaultsOnly)
	float _growthRate;

	UPROPERTY(EditDefaultsOnly)
	float _recoverPercentSecond;

	float _previousValue;
	float _elapsedTime;
};