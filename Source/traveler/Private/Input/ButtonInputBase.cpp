// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputBase.h"

DEFINE_LOG_CATEGORY(LogMyInput);


UButtonInputBase::UButtonInputBase()
{
}

void UButtonInputBase::Press()
{
	_isPressing = true;
	VOnPressed();
}

void UButtonInputBase::Pressing(float deltaTime)
{
	if (_isPressing)
	{
		_pressingTime += deltaTime;
		VOnPressing(deltaTime);
	}
}

void UButtonInputBase::Release()
{
	VOnReleased();
	_isPressing = false;
}

float UButtonInputBase::GetPressingTime()
{
	return _pressingTime;
}

bool UButtonInputBase::IsPressing()
{
	return _isPressing;
}

void UButtonInputBase::VOnPressed()
{
}

void UButtonInputBase::VOnPressing(float deltaTime)
{
}

void UButtonInputBase::VOnReleased()
{
}
