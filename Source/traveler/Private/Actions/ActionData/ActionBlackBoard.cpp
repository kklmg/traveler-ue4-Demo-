// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionBlackBoard.h"

void UActionBlackBoard::WriteData_Bool(EActionDataKey key, bool value)
{
	auto data = GetOrCreateDataAs<UDataBool>(key);
	data->Value = value;
	NotifyData(key);
}

void UActionBlackBoard::WriteData_Int32(EActionDataKey key, int32 value)
{
	auto data = GetOrCreateDataAs<UDataInt32>(key);
	data->Value = value;
	NotifyData(key);
}

void UActionBlackBoard::WriteData_Float(EActionDataKey key, float value)
{
	auto data = GetOrCreateDataAs<UDataFloat>(key);
	data->Value = value;
	NotifyData(key);
}

void UActionBlackBoard::WriteData_FVector(EActionDataKey key, FVector value)
{
	auto data = GetOrCreateDataAs<UDataVector>(key);
	data->Value = value;
	NotifyData(key);
}

void UActionBlackBoard::WriteData_UObject(EActionDataKey key, UObject* value)
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

bool UActionBlackBoard::TryGetData_Bool(EActionDataKey key, bool& outValue,bool bConsumeData)
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

bool UActionBlackBoard::TryGetData_Int32(EActionDataKey key, int32& outValue, bool bConsumeData)
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

bool UActionBlackBoard::TryGetData_Float(EActionDataKey key, float& outValue, bool bConsumeData)
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

bool UActionBlackBoard::TryGetData_FVector(EActionDataKey key, FVector& outValue, bool bConsumeData)
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

UObject* UActionBlackBoard::GetData_UObject(EActionDataKey key, bool bConsumeData)
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

void UActionBlackBoard::DeleteData(EActionDataKey key)
{
	_mapData.Remove(key);
}

void UActionBlackBoard::NotifyData(EActionDataKey key)
{
	if (_mapData.Contains(key) && _mapDataDelegates.Contains(key))
	{
		_mapDataDelegates[key].Broadcast(_mapData[key]);
	}
}
