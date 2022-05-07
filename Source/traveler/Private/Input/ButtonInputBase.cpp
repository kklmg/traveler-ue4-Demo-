// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputBase.h"

DEFINE_LOG_CATEGORY(LogMyInput);


UButtonInputBase::UButtonInputBase()
{
}

void UButtonInputBase::OnPressed()
{
	_isPressing = true;
	VTMPress();
}

void UButtonInputBase::OnPressing(float deltaTime)
{
	if (_isPressing)
	{
		_pressingTime += deltaTime;
		VTMPressing(deltaTime);
	}
}

void UButtonInputBase::OnReleased()
{
	VTMRelease();
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

void UButtonInputBase::VTMPress()
{
}

void UButtonInputBase::VTMPressing(float deltaTime)
{
}

void UButtonInputBase::VTMRelease()
{
}
