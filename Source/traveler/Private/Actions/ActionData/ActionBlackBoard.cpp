// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionBlackBoard.h"

void UActionBlackBoard::WriteData_Bool(EActionData key, bool value)
{
	_boolData.WriteData(key,value);
}

void UActionBlackBoard::WriteData_Int(EActionData key, int value)
{
	_intData.WriteData(key, value);
}

void UActionBlackBoard::WriteData_Float(EActionData key, float value)
{
	_floatData.WriteData(key, value);
}

void UActionBlackBoard::WriteData_FVector(EActionData key, FVector value)
{
	_vectorData.WriteData(key, value);
}

void UActionBlackBoard::WriteData_UObject(EActionData key, UObject* value)
{
	_objectData.WriteData(key, value);
}

bool UActionBlackBoard::TryGetData_Bool(EActionData key, bool& outValue,bool bConsumeData)
{
	return _boolData.TryGetData(key,outValue);
}

bool UActionBlackBoard::TryGetData_Int(EActionData key, int& outValue, bool bConsumeData)
{
	return _intData.TryGetData(key, outValue);
}

bool UActionBlackBoard::TryGetData_Float(EActionData key, float& outValue, bool bConsumeData)
{
	return _floatData.TryGetData(key, outValue);
}

bool UActionBlackBoard::TryGetData_FVector(EActionData key, FVector& outValue, bool bConsumeData)
{
	return _vectorData.TryGetData(key,outValue);
}

bool UActionBlackBoard::TryGetData_UObject(EActionData key, UObject** outValue, bool bConsumeData)
{
	return _objectData.TryGetData(key, *outValue);
}

void UActionBlackBoard::DeleteData(EActionData key)
{
	_intData.DeleteData(key);
	_floatData.DeleteData(key);
	_vectorData.DeleteData(key);
	_quatData.DeleteData(key);
	_objectData.DeleteData(key);
}