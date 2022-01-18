// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputBase.h"
#include "..\..\Public\Input\ButtonInputBase.h"

DEFINE_LOG_CATEGORY(LogMyInput);


UButtonInputBase::UButtonInputBase()
{
	_buttonName = TEXT("unKnown");
}

void UButtonInputBase::Tick(float deltaTime)
{
	if(_isPressing)
	{
		_holdingTime += deltaTime;
	}
}

void UButtonInputBase::VPress()
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
}

void UButtonInputBase::VRelease()
{
	if (OnButtonPressed.IsBound())
	{
		OnButtonPressed.Execute(this);
	}
	else
	{
		UE_LOG(LogMyInput, Warning, TEXT("Released Button_ %s: delegate is not bound"), *_buttonName);
	}
	_isPressing = false;
}

FName UButtonInputBase::GetActionName()
{
	return _actionName;
}

float UButtonInputBase::GetHoldingTime()
{
	return _holdingTime;
}

bool UButtonInputBase::IsPressing()
{
	return _isPressing;
}
