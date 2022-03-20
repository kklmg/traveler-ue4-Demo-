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


UReactive_Int* UAnimationModelBase::GetData_Int(FName dataKey)
{
	return GetOrCreate<UReactive_Int>(dataKey);
}

UReactive_Float* UAnimationModelBase::GetData_Float(FName dataKey)
{
	return GetOrCreate<UReactive_Float>(dataKey);
}

UReactive_Bool* UAnimationModelBase::GetData_Bool(FName dataKey)
{
	return GetOrCreate<UReactive_Bool>(dataKey);
}

UReactive_UInt8* UAnimationModelBase::GetData_UInt8(FName dataKey)
{
	return GetOrCreate<UReactive_UInt8>(dataKey);
}

UReactive_Vector* UAnimationModelBase::GetData_Vector(FName dataKey)
{
	return GetOrCreate<UReactive_Vector>(dataKey);
}

UReactive_Quat* UAnimationModelBase::GetData_Quat(FName dataKey)
{
	return GetOrCreate<UReactive_Quat>(dataKey);
}

UReactive_UObject* UAnimationModelBase::GetData_UObject(FName dataKey)
{
	return GetOrCreate<UReactive_UObject>(dataKey);
}

void UAnimationModelBase::SetInt(FName dataKey, int value)
{
	UReactive_Int* data = GetOrCreate<UReactive_Int>(dataKey);
	if(data) 
	{
		data->SetValue(value);
	}
}

void UAnimationModelBase::SetFloat(FName dataKey, float value)
{
	UReactive_Float* data = GetOrCreate<UReactive_Float>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UAnimationModelBase::SetBool(FName dataKey, bool value)
{
	UReactive_Bool* data = GetOrCreate<UReactive_Bool>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UAnimationModelBase::SetVector(FName dataKey, FVector value)
{
	UReactive_Vector* data = GetOrCreate<UReactive_Vector>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UAnimationModelBase::SetQuat(FName dataKey, FQuat value)
{
	UReactive_Quat* data = GetOrCreate<UReactive_Quat>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UAnimationModelBase::SetUInt8(FName dataKey, uint8 value)
{
	UReactive_UInt8* data = GetOrCreate<UReactive_UInt8>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}

void UAnimationModelBase::SetUObject(FName dataKey, UObject* value)
{
	UReactive_UObject* data = GetOrCreate<UReactive_UObject>(dataKey);
	if (data)
	{
		data->SetValue(value);
	}
}
