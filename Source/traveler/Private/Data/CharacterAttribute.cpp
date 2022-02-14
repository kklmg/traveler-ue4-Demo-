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
	_recoverPercentSecond = attributeRow->RecoverPercentPerSecond;
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

void UCharacterAttribute::Tick(float deltaTime)
{
	if(_canRecover)
	{
		_elapsedTimeFromLastRecover += deltaTime;

		//execute recover
		if (_elapsedTimeFromLastRecover > 0.5f)
		{
			float recovery = _maxValue * _recoverPercentSecond * 0.5f;
			ApplyValueChange(recovery);
			_elapsedTimeFromLastRecover = 0.0f;
		}
	}
	else
	{
		_elapsedTimeFromLastValueChanged += deltaTime;

		if (_elapsedTimeFromLastValueChanged > 1.0f)
		{
			_canRecover = true;
		}
	}
}



void UCharacterAttribute::SetValue(float newValue)
{
	newValue = FMath::Clamp(newValue, _minValue, _maxValue);

	if (newValue == _currentValue)return;

	_previousValue = _currentValue;
	_currentValue = newValue;

	ResetLastValueChangedTimer();

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

void UCharacterAttribute::ResetLastValueChangedTimer()
{
	_elapsedTimeFromLastValueChanged = 0.0f;
	_canRecover = false;
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