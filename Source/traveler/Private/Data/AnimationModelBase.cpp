// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/AnimationModelBase.h"

UReactiveDataBase* UAnimationModelBase::GetData(FName dataKey)
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


void UAnimationModelBase::SetInt(FName dataKey, int value)
{
	if (_dataMap.Contains(dataKey))
	{
		UReactive_Int* data = Cast<UReactive_Int>(_dataMap[dataKey]);

		if(data)
		{
			data->SetValue(value);
		}
	}
	else
	{
		UReactive_Int* newData = NewObject<UReactive_Int>(this);
		newData->SetValue(value);
		_dataMap.Add(dataKey, newData);
	}
}

void UAnimationModelBase::SetFloat(FName dataKey, float value)
{
	if (_dataMap.Contains(dataKey))
	{
		UReactive_Int* data = Cast<UReactive_Int>(_dataMap[dataKey]);

		if (data)
		{
			data->SetValue(value);
		}
	}
	else
	{
		UReactive_Int* newData = NewObject<UReactive_Int>(this);
		newData->SetValue(value);
		_dataMap.Add(dataKey, newData);
	}
}

void UAnimationModelBase::SetBool(FName dataKey, bool value)
{
	if (_dataMap.Contains(dataKey))
	{
		UReactive_Float* data = Cast<UReactive_Float>(_dataMap[dataKey]);

		if (data)
		{
			data->SetValue(value);
		}
	}
	else
	{
		UReactive_Float* newData = NewObject<UReactive_Float>(this);
		newData->SetValue(value);
		_dataMap.Add(dataKey, newData);
	}
}

void UAnimationModelBase::SetVector(FName dataKey, FVector value)
{
	if (_dataMap.Contains(dataKey))
	{
		UReactive_Vector* data = Cast<UReactive_Vector>(_dataMap[dataKey]);

		if (data)
		{
			data->SetValue(value);
		}
	}
	else
	{
		UReactive_Vector* newData = NewObject<UReactive_Vector>(this);
		newData->SetValue(value);
		_dataMap.Add(dataKey, newData);
	}
}

void UAnimationModelBase::SetQuat(FName dataKey, FQuat value)
{
	if (_dataMap.Contains(dataKey))
	{
		UReactive_Quat* data = Cast<UReactive_Quat>(_dataMap[dataKey]);

		if (data)
		{
			data->SetValue(value);
		}
	}
	else
	{
		UReactive_Quat* newData = NewObject<UReactive_Quat>(this);
		newData->SetValue(value);
		_dataMap.Add(dataKey, newData);
	}
}
