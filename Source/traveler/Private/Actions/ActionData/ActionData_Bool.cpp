// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionData_Bool.h"

void UActionData_Bool::SetValue(bool value)
{
	_value = value;
}
bool UActionData_Bool::GetValue()
{
	return _value;
}