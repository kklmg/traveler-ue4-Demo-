// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AxisInputBase.h"

UAxisInputBase::UAxisInputBase()
{
}

void UAxisInputBase::Tick(float deltaTime)
{
}

void UAxisInputBase::VHandleInput(float value)
{
}

EInputType UAxisInputBase::GetInputType()
{
	return _inputType;
}
