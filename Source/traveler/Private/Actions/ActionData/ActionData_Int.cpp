// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionData_Int.h"

int UActionData_Int::GetValue()
{
	return _value;
}

void UActionData_Int::SetValue(int value)
{
	_value = value;
}
