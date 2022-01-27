// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputBase.h"
#include "..\..\Public\Input\ButtonInputBase.h"

DEFINE_LOG_CATEGORY(LogMyInput);


UButtonInputBase::UButtonInputBase()
{
	_buttonName = TEXT("unKnown");
}

void UButtonInputBase::Press()
{
	if (OnButtonPressed.IsBound()) 
	{
		OnButtonPressed.Execute(this);
	}
	else
	{
		UE_LOG(LogMyInput,Warning, TEXT("pressed Button_ %s: delegate is not bound"), *_buttonName);
	}
	_isPressing = true;

	VTMPress();
}

void UButtonInputBase::Pressing(float deltaTime)
{
	if (_isPressing)
	{
		_holdingTime += deltaTime;
		VTMPressing(deltaTime);
	}
}

void UButtonInputBase::Release()
{
	if (OnButtonPressed.IsBound())
	{
		OnButtonPressed.Execute(this);
	}
	else
	{
		UE_LOG(LogMyInput, Warning, TEXT("Released Button_ %s: delegate is not bound"), *_buttonName);
	}

	VTMRelease();

	_isPressing = false;
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

FName UButtonInputBase::GetInputMappingName()
{
	return _inputMappingName;
}

float UButtonInputBase::GetHoldingTime()
{
	return _holdingTime;
}

bool UButtonInputBase::IsPressing()
{
	return _isPressing;
}
