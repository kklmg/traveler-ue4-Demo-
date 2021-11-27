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