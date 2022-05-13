// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIProcess/FlickeringUIProcess.h"

void UFlickeringUIProcess::VOnInit()
{
	Super::VOnInit();
	_remainingTime = _duration;
}

void UFlickeringUIProcess::SetDuration(float duration)
{
	_duration = duration;
	_remainingTime = duration;
}

void UFlickeringUIProcess::SetOpacityCurve(UCurveFloat* opacityCurve)
{
	_opacityCurve = opacityCurve;
}


bool UFlickeringUIProcess::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	return (_opacityCurve && _duration > 0.0f);
}

void UFlickeringUIProcess::VOnExecute()
{
	Super::VOnExecute();

}

void UFlickeringUIProcess::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	_remainingTime -= deltaTime;

	float normalizedElapsedTime = (_duration - _remainingTime) / _duration;
	float opacityValue = _opacityCurve->GetFloatValue(normalizedElapsedTime);
	UWidget* widget = GetWidget();

	if(widget)
	{
		widget->SetRenderOpacity(opacityValue);
	}

	if (_remainingTime <= 0.0f)
	{
		SetProcessSucceed();
	}
}


void UFlickeringUIProcess::VOnDead()
{
	Super::VOnDead();
}

void UFlickeringUIProcess::VOnSucceed()
{
	Super::VOnSucceed();
}

void UFlickeringUIProcess::VOnFailed()
{
	Super::VOnFailed();
}

void UFlickeringUIProcess::VOnAborted()
{
	Super::VOnAborted();
}
