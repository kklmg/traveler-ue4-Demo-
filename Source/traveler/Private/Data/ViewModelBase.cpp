// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ViewModelBase.h"

UReactiveDataBase* UViewModelBase::GetData(FName dataKey)
{
	if (_dataMap.Contains(dataKey))
	{
		return _dataMap[dataKey];
	}
	else
	{
		return nullptr;
	}
}


UReactive_Int* UViewModelBase::GetData_Int(FName dataKey)
{
	return GetOrCreate<UReactive_Int>(dataKey);
}

UReactive_Float* UViewModelBase::GetData_Float(FName dataKey)
{
	return GetOrCreate<UReactive_Float>(dataKey);
}

UReactive_Bool* UViewModelBase::GetData_Bool(FName dataKey)
{
	return GetOrCreate<UReactive_Bool>(dataKey);
}

UReactive_UInt8* UViewModelBase::GetData_UInt8(FName dataKey)
{
	return GetOrCreate<UReactive_UInt8>(dataKey);
}

UReactive_Vector* UViewModelBase::GetData_Vector(FName dataKey)
{
	return GetOrCreate<UReactive_Vector>(dataKey);
}

UReactive_Quat* UViewModelBase::GetData_Quat(FName dataKey)
{
	return GetOrCreate<UReactive_Quat>(dataKey);
}

UReactive_UObject* UViewModelBase::GetData_UObject(FName dataKey)
{
	return GetOrCreate<UReactive_UObject>(dataKey);
}

void UViewModelBase::SetInt(FName dataKey, int value)
{
	UReactive_Int* data = GetOrCreate<UReactive_Int>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UViewModelBase::SetFloat(FName dataKey, float value)
{
	UReactive_Float* data = GetOrCreate<UReactive_Float>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UViewModelBase::SetBool(FName dataKey, bool value)
{
	UReactive_Bool* data = GetOrCreate<UReactive_Bool>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UViewModelBase::SetVector(FName dataKey, FVector value)
{
	UReactive_Vector* data = GetOrCreate<UReactive_Vector>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UViewModelBase::SetQuat(FName dataKey, FQuat value)
{
	UReactive_Quat* data = GetOrCreate<UReactive_Quat>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UViewModelBase::SetUInt8(FName dataKey, uint8 value)
{
	UReactive_UInt8* data = GetOrCreate<UReactive_UInt8>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UViewModelBase::SetUObject(FName dataKey, UObject* value)
{
	UReactive_UObject* data = GetOrCreate<UReactive_UObject>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UViewModelBase::ClearData()
{
	for (auto pair : _dataMap)
	{
		if (pair.Value)
		{
			pair.Value->VClearData();
		}
	}

	_dataMap.Empty();
}
