// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ViewModel.h"

void UReactive_Bool::SetValue(bool value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

void UReactive_Int::SetValue(int value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

void UReactive_Float::SetValue(float value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

void UReactive_Quat::SetValue(FQuat value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

void UReactive_Vector::SetValue(FVector value)
{
	if (_value == value) return;
	_value = value;
	OnValueChanged.Broadcast(_value);
}

