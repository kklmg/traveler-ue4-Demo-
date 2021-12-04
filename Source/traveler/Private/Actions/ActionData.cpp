// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData.h"


void UActionData::SetMovementInput(FVector movementInput)
{
	_movementInput = movementInput;
	OnReceiveMovementDelegate.Broadcast(movementInput);
}

FVector UActionData::GetMovementInput()
{
	return _movementInput;
}

void UActionData::WriteVectorData(FName key, FVector value) 
{
	if (_mapVectorData.Contains(key)) 
	{
		_mapVectorData[key] = value;
	}
	else
	{
		_mapVectorData.Add(key, value);
	}
}

bool UActionData::TryReadVectorData(FName key, FVector& outValue)
{
	if (_mapVectorData.Contains(key))
	{
		outValue = _mapVectorData[key];
		return true;
	}
	return false;
}

void UActionData::WriteFloatData(FName key, float value)
{
	if (_mapFloatData.Contains(key))
	{
		_mapFloatData[key] = value;
	}
	else
	{
		_mapFloatData.Add(key, value);
	}
}

bool UActionData::TryReadFloatData(FName key, float& outValue)
{
	if (_mapFloatData.Contains(key))
	{
		outValue = _mapFloatData[key];
		return true;
	}
	return false;
}

void UActionData::WriteUObjectData(FName key, UObject* value)
{
	if (value == nullptr)
	{
		return;
	}

	if (_mapUObjectData.Contains(key))
	{
		_mapUObjectData[key] = value;
	}
	else
	{
		_mapUObjectData.Add(key, value);
	}
}

bool UActionData::TryReadUObjectData(FName key, UObject** outValue)
{
	if (_mapUObjectData.Contains(key))
	{
		*outValue = _mapUObjectData[key];
		return true;
	}
	return false;
}