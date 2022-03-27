// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionBlackBoard.h"

void UActionBlackBoard::WriteData_Bool(EActionDataKey key, bool value)
{
	_boolData.WriteData(key,value);
}

void UActionBlackBoard::WriteData_Int(EActionDataKey key, int value)
{
	_intData.WriteData(key, value);
}

void UActionBlackBoard::WriteData_Float(EActionDataKey key, float value)
{
	_floatData.WriteData(key, value);
}

void UActionBlackBoard::WriteData_FVector(EActionDataKey key, FVector value)
{
	_vectorData.WriteData(key, value);
}

//void UActionBlackBoard::WriteData_UObject(EActionDataKey key, UObject* value)
//{
//	_objectData.WriteData(key, value);
//}

bool UActionBlackBoard::TryGetData_Bool(EActionDataKey key, bool& outValue,bool bConsumeData)
{
	return _boolData.TryGetData(key,outValue);
}

bool UActionBlackBoard::TryGetData_Int(EActionDataKey key, int& outValue, bool bConsumeData)
{
	return _intData.TryGetData(key, outValue);
}

bool UActionBlackBoard::TryGetData_Float(EActionDataKey key, float& outValue, bool bConsumeData)
{
	return _floatData.TryGetData(key, outValue);
}

bool UActionBlackBoard::TryGetData_FVector(EActionDataKey key, FVector& outValue, bool bConsumeData)
{
	return _vectorData.TryGetData(key,outValue);
}

//bool UActionBlackBoard::TryGetData_UObject(EActionDataKey key, UObject** outValue, bool bConsumeData)
//{
//	return _objectData.TryGetData(key, *outValue);
//}

TMulticastDelegate<void(bool)>& UActionBlackBoard::GetValueChangedDelegate_Bool(EActionDataKey key)
{
	return _boolData.GetDelegate(key);
}

TMulticastDelegate<void(int)>& UActionBlackBoard::GetValueChangedDelegate_Int(EActionDataKey key)
{
	return _intData.GetDelegate(key);
}

TMulticastDelegate<void(float)>& UActionBlackBoard::GetValueChangedDelegate_Float(EActionDataKey key)
{
	return _floatData.GetDelegate(key);
}

TMulticastDelegate<void(FVector)>& UActionBlackBoard::GetValueChangedDelegate_FVector(EActionDataKey key)
{
	return _vectorData.GetDelegate(key);
}

TMulticastDelegate<void(FQuat)>& UActionBlackBoard::GetValueChangedDelegate_Fquat(EActionDataKey key)
{
	return _quatData.GetDelegate(key);
}

void UActionBlackBoard::DeleteData(EActionDataKey key)
{
	_intData.DeleteData(key);
	_floatData.DeleteData(key);
	_vectorData.DeleteData(key);
	_quatData.DeleteData(key);
	//_objectData.DeleteData(key);
}