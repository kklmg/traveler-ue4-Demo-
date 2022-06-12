// Fill out your copyright notice in the Description page of Project Settings.


#include "Status/BasicStatus.h"
#include "Math/UnrealMathUtility.h"

void UBasicStatus::VInitialize(const FStatusTableRow& tableRow, int32 level)
{
	Super::VInitialize(tableRow, level);

	_remainingValue = GetFinalValue();
	_recovery = tableRow.Recovery;

	OnRemainingValueChanged.Broadcast(_remainingValue, _remainingValue);
}

void UBasicStatus::Tick(float deltaTime)
{
	if (_bCanRecover == false) return;

	_elapsedTimeFromLastValueChanged += deltaTime;

	if (_remainingValue < GetFinalValue() && _recovery > 0.0f && _elapsedTimeFromLastValueChanged > 1.0f)
	{
		_elapsedTimeFromLastRecover += deltaTime;

		//execute recover
		while (_elapsedTimeFromLastRecover > 1.0f)
		{
			_elapsedTimeFromLastRecover -= 1.0f;

			//execute recovery
			ApplyValueChange(GetFinalValue() * _recovery, false);
		}

		//reset timer 
		if (_remainingValue >= GetFinalValue())
		{
			_elapsedTimeFromLastRecover = 0.0f;
		}
	}
}

void UBasicStatus::SetCanRecover(bool bCanRecover)
{
	_bCanRecover = bCanRecover;
	if (bCanRecover == false)
	{
		_elapsedTimeFromLastRecover = 0.0f;
		_elapsedTimeFromLastValueChanged = 0.0f;
	}

}

float UBasicStatus::GetRemainingValue()
{
	return _remainingValue;
}

float UBasicStatus::GetPercentage()
{
	return _remainingValue / GetFinalValue();
}

void UBasicStatus::ApplyValueChange(float deltaValue, bool bResetRecoveryTimer)
{
	float cacheValue = _remainingValue;

	_remainingValue = FMath::Clamp(_remainingValue + deltaValue, 0.0f, GetFinalValue());

	if (_remainingValue != cacheValue)
	{
		OnRemainingValueChanged.Broadcast(cacheValue, _remainingValue);
	}

	if(bResetRecoveryTimer)
	{
		_elapsedTimeFromLastValueChanged = 0.0f;
	}
}

void UBasicStatus::VOnLevelChanged(int32 level)
{
	Super::VOnLevelChanged(level);

	float cacheValue = _remainingValue;
	_remainingValue = GetFinalValue();

	OnRemainingValueChanged.Broadcast(cacheValue, _remainingValue);
}


