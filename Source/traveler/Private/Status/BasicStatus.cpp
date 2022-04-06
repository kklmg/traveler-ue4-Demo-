// Fill out your copyright notice in the Description page of Project Settings.


#include "Status/BasicStatus.h"

void UBasicStatus::VInitialize(const FStatusTableRow& tableRow, int32 level)
{
	Super::VInitialize(tableRow, level);

	_remainingValue = GetFinalValue();
	_recovery = tableRow.Recovery;
}

float UBasicStatus::GetRemainingValue()
{
	return _remainingValue;
}

float UBasicStatus::GetPercentage()
{
	return _remainingValue / GetFinalValue();
}

void UBasicStatus::ApplyValueChange(float value)
{
	_remainingValue -= value;
}
