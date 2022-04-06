// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ViewModel.h"

void UReactive_Bool::SetValue(bool value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

bool UReactive_Bool::GetValue()
{
	return _value;
}

void UReactive_Int::SetValue(int value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

int UReactive_Int::GetValue()
{
	return _value;
}

void UReactive_Float::SetValue(float value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

float UReactive_Float::GetValue()
{
	return _value;
}

void UReactive_Quat::SetValue(FQuat value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

FQuat UReactive_Quat::GetValue()
{
	return _value;
}

void UReactive_Vector::SetValue(FVector value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

FVector UReactive_Vector::GetValue()
{
	return _value;
}

void UReactive_UInt8::SetValue(uint8 value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

uint8 UReactive_UInt8::GetValue()
{
	return _value;
}

void UReactive_UObject::SetValue(UObject* value)
{
	//if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

UObject* UReactive_UObject::GetValue()
{
	return _value;
}
