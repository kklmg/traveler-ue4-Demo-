// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterAttribute.h"
#include "Data/AttributeData.h"

UCharacterAttribute::UCharacterAttribute()
{
	_currentValue = 0;
	_minValue = TNumericLimits<float>::Min();
	_maxValue = TNumericLimits<float>::Max();
	_previousValue = 0;
}

void UCharacterAttribute::Initialize(FAttributeRow* attributeRow , int level)
{
	_attributeType = attributeRow->AttributeType;
	_attributeText = attributeRow->GetLocaleText();

	_currentValue = attributeRow->GetGrowedValue(level);
	_previousValue = _currentValue;

	_minValue = 0;
	_maxValue = _currentValue;

	_growthRate = attributeRow->GrowthRate;
}

void UCharacterAttribute::Initialize(EAttributeType attributeType, FText attributeText, float value, float growthRate)
{
	_attributeType = attributeType;
	_attributeText = attributeText;
	_currentValue = value;
	_previousValue = value;
	_growthRate = growthRate;
}

void UCharacterAttribute::Initialize(EAttributeType attributeType, FText attributeText, float value, float minValue, float maxValue, float growthRate)
{
	_attributeType = attributeType;
	_attributeText = attributeText;
	_minValue = minValue;
	_maxValue = maxValue;
	_currentValue = value;
	_previousValue = value;
	_growthRate = growthRate;
}



void UCharacterAttribute::SetValue(float newValue)
{
	newValue = FMath::Clamp(newValue, _minValue, _maxValue);

	_previousValue = _currentValue;
	_currentValue = newValue;

	onValueChanged.Broadcast(_previousValue, _currentValue);
}

void UCharacterAttribute::ApplyValueChange(float deltaValue)
{
	SetValue(_currentValue + deltaValue);
}

FORCEINLINE EAttributeType UCharacterAttribute::GetAttributeType()
{
	return _attributeType;
}

FORCEINLINE FText UCharacterAttribute::GetText()
{
	return _attributeText;
}

FORCEINLINE float UCharacterAttribute::GetValue()
{
	return _currentValue;
}


FORCEINLINE float UCharacterAttribute::GetMinValue()
{
	return _minValue;
}

FORCEINLINE float UCharacterAttribute::GetMaxValue()
{
	return _maxValue;
}

float UCharacterAttribute::GetPercentage()
{
	return _currentValue/_maxValue;
}

FORCEINLINE float UCharacterAttribute::GetPreviousValue()
{
	return _previousValue;
}