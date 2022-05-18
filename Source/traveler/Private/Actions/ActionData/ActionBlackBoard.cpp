// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionBlackBoard.h"

void UActionBlackBoard::WriteData_Bool(FName key, bool value)
{
	auto data = GetOrCreateDataAs<UDataBool>(key);
	if (!data) return;

	data->Value = value;
	NotifyData(key);
}

void UActionBlackBoard::WriteData_Int32(FName key, int32 value)
{
	auto data = GetOrCreateDataAs<UDataInt32>(key);
	if (!data) return;

	data->Value = value;
	NotifyData(key);
}

void UActionBlackBoard::WriteData_Float(FName key, float value)
{
	auto data = GetOrCreateDataAs<UDataFloat>(key);
	if(!data) return;

	data->Value = value;
	NotifyData(key);
}

void UActionBlackBoard::WriteData_FVector(FName key, FVector value)
{
	auto data = GetOrCreateDataAs<UDataVector>(key);
	if (!data) return;

	data->Value = value;
	NotifyData(key);
}

void UActionBlackBoard::WriteData_UObject(FName key, UObject* value)
{
	if (_mapData.Contains(key))
	{
		_mapData[key] = value;
	}
	else
	{
		_mapData.Add(key, value);
	}
	NotifyData(key);
}

bool UActionBlackBoard::TryGetData_Bool(FName key, bool& outValue,bool bConsumeData)
{
	auto data = GetDataAs<UDataBool>(key);
	if(data)
	{
		outValue = data->Value;
		if(bConsumeData)
		{
			_mapData.Remove(key);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool UActionBlackBoard::TryGetData_Int32(FName key, int32& outValue, bool bConsumeData)
{
	auto data = GetDataAs<UDataInt32>(key);
	if (data)
	{
		outValue = data->Value;
		if (bConsumeData)
		{
			_mapData.Remove(key);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool UActionBlackBoard::TryGetData_Float(FName key, float& outValue, bool bConsumeData)
{
	auto data = GetDataAs<UDataFloat>(key);
	if (data)
	{
		outValue = data->Value;
		if (bConsumeData)
		{
			_mapData.Remove(key);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool UActionBlackBoard::TryGetData_FVector(FName key, FVector& outValue, bool bConsumeData)
{
	auto data = GetDataAs<UDataVector>(key);
	if (data)
	{
		outValue = data->Value;
		if (bConsumeData)
		{
			_mapData.Remove(key);
		}
		return true;
	}
	else
	{
		return false;
	}
}

UObject* UActionBlackBoard::GetData_UObject(FName key, bool bConsumeData)
{
	if(_mapData.Contains(key))
	{
		UObject* data = _mapData[key];

		if (bConsumeData)
		{
			_mapData.Remove(key);
		}

		return data;
	}
	else
	{
		return nullptr;
	}
}

void UActionBlackBoard::DeleteData(FName key)
{
	_mapData.Remove(key);
}

void UActionBlackBoard::NotifyData(FName key)
{
	if (_mapData.Contains(key) && _mapDataDelegates.Contains(key))
	{
		_mapDataDelegates[key].Broadcast(_mapData[key]);
	}
}
