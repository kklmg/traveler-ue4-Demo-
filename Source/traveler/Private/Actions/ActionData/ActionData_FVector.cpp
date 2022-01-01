// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionData/ActionData_FVector.h"

FVector UActionData_FVector::GetValue()
{
	return _value;
}

void UActionData_FVector::SetValue(FVector value)
{
	_value = value;
}
