// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actions/ActionData/ActionDataBase.h"
#include "Actions/ActionData/ActionData_Bool.h"
#include "Actions/ActionData/ActionData_Int.h"
#include "Actions/ActionData/ActionData_Float.h"
#include "Actions/ActionData/ActionData_FVector.h"
#include "Actions/ActionData/ActionData_UObject.h"

void UActionBlackBoard::WriteData_Bool(EActionData key, bool value)
{
	UActionData_Bool* data = GetOrCreateData<UActionData_Bool>(key);
	data->SetValue(value);
}

void UActionBlackBoard::WriteData_Int(EActionData key, int value)
{
	UActionData_Int* data = GetOrCreateData<UActionData_Int>(key);
	data->SetValue(value);
}

void UActionBlackBoard::WriteData_Float(EActionData key, float value)
{
	UActionData_Float* data = GetOrCreateData<UActionData_Float>(key);
	data->SetValue(value);
}

void UActionBlackBoard::WriteData_FVector(EActionData key, FVector value)
{
	UActionData_FVector* data = GetOrCreateData<UActionData_FVector>(key);
	data->SetValue(value);
}

void UActionBlackBoard::WriteData_UObject(EActionData key, UObject* value)
{
	UActionData_UObject* data = GetOrCreateData<UActionData_UObject>(key);
	data->SetValue(value);
}


UActionDataBase* UActionBlackBoard::GetData(EActionData key)
{
	if (_mapActionData.Contains(key))
	{
		return _mapActionData[key];
	}
	else
	{
		return nullptr;
	}
}

void UActionBlackBoard::DeleteData(EActionData key)
{
	_mapActionData.Remove(key);
}

bool UActionBlackBoard::TryGetData_Bool(EActionData key, bool& outValue,bool bConsumeData)
{
	UActionData_Bool* data = GetData<UActionData_Bool>(key);

	if (data)
	{
		outValue = data->GetValue();
		if (bConsumeData)
		{
			DeleteData(key);
		}
		return true;
	}
	return false;
}

bool UActionBlackBoard::TryGetData_Int(EActionData key, int& outValue, bool bConsumeData)
{
	UActionData_Int* data = GetData<UActionData_Int>(key);

	if(data)
	{
		outValue = data->GetValue();
		if(bConsumeData)
		{
			DeleteData(key);
		}
		return true;
	}
	return false;
}

bool UActionBlackBoard::TryGetData_Float(EActionData key, float& outValue, bool bConsumeData)
{
	UActionData_Float* data = GetData<UActionData_Float>(key);

	if (data)
	{
		outValue = data->GetValue();
		if (bConsumeData)
		{
			DeleteData(key);
		}
		return true;
	}
	return false;
}

bool UActionBlackBoard::TryGetData_FVector(EActionData key, FVector& outValue, bool bConsumeData)
{
	UActionData_FVector* data = GetData<UActionData_FVector>(key);

	if (data)
	{
		outValue = data->GetValue();
		if (bConsumeData)
		{
			DeleteData(key);
		}
		return true;
	}
	return false;
}

bool UActionBlackBoard::TryGetData_UObject(EActionData key, UObject** outValue, bool bConsumeData)
{
	UActionData_UObject* data = GetData<UActionData_UObject>(key);

	if (data)
	{
		*outValue = data->GetValue();
		if (bConsumeData)
		{
			DeleteData(key);
		}
		return true;
	}
	return false;
}
