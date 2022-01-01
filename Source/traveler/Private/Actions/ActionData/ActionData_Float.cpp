// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionData_Float.h"

float UActionData_Float::GetValue()
{
	return _value;
}

void UActionData_Float::SetValue(float value)
{
	_value = value;
}
