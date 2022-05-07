// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AxisInputDelegate.h"

void UAxisInputDelegate::VHandleInputAxis(float value)
{
	_axisInputDelegate.ExecuteIfBound(value);
}
