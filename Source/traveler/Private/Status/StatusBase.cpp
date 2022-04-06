// Fill out your copyright notice in the Description page of Project Settings.


#include "Status/StatusBase.h"

UStatusBase::UStatusBase()
{
}

void UStatusBase::VInitialize(const FStatusTableRow& tableRow, int32 level)
{
	_statusType = tableRow.StatusType;
	//_statusText =	
	_growth = tableRow.Growth;
	_primaryValue = tableRow.Value;
	_basicValue = _primaryValue + (_growth * level);
	_finalValue = _basicValue;
}

float UStatusBase::GetPrimaryValue()
{
	return _primaryValue;
}

float UStatusBase::GetBasicValue()
{
	return _basicValue;
}

float UStatusBase::GetFinalValue()
{
	return  _finalValue;
}

EStatusType UStatusBase::GetStatusType()
{
	return _statusType;
}

FText UStatusBase::GetText()
{
	return _statusText;
}

void UStatusBase::VOnLevelUp(int32 level)
{
	_basicValue = _primaryValue + (_growth * level);
}

void UStatusBase::ComputeFinalValue()
{
	//To do
	_finalValue = _basicValue;
}
