// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputBase.h"

DEFINE_LOG_CATEGORY(LogMyInput);


UButtonInputBase::UButtonInputBase()
{
}

void UButtonInputBase::OnPressed()
{
	_isPressing = true;
	VTMOnPressed();
}

void UButtonInputBase::OnPressing(float deltaTime)
{
	if (_isPressing)
	{
		_pressingTime += deltaTime;
		VTMOnPressing(deltaTime);
	}
}

void UButtonInputBase::OnReleased()
{
	VTMOnReleased();
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

void UButtonInputBase::VTMOnPressed()
{
}

void UButtonInputBase::VTMOnPressing(float deltaTime)
{
}

void UButtonInputBase::VTMOnReleased()
{
}
