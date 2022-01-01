// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionData_UObject.h"

UObject* UActionData_UObject::GetValue()
{
	return _value;
}

void UActionData_UObject::SetValue(UObject* value)
{
	_value = value;
}
