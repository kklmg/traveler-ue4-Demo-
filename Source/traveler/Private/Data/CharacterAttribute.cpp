// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterAttribute.h"

UCharacterAttribute::UCharacterAttribute()
{
	_currentValue = 0;
	_minValue = TNumericLimits<float>::Min();
	_maxValue = TNumericLimits<float>::Max();
	_previousValue = 0;
}

FORCEINLINE FName UCharacterAttribute::GetName()
{
	return _AttributeName;
}

void UCharacterAttribute::Initialize(FName attributeName, float value)
{
	_AttributeName = attributeName;
	_currentValue = value;
	_previousValue = value;
}

void UCharacterAttribute::Initialize(FName attributeName, float value, float minValue, float maxValue)
{
	_AttributeName = attributeName;
	_minValue = minValue;
	_maxValue = maxValue;
	_currentValue = value;
	_previousValue = value;
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