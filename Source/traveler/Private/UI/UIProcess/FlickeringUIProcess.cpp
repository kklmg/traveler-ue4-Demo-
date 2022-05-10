// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIProcess/FlickeringUIProcess.h"

void UFlickeringUIProcess::VOnInit()
{
	Super::VOnInit();
	_elapsedTime = 0.0f;
}

void UFlickeringUIProcess::SetDuration(float duration)
{
	_duration = duration;
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

	_elapsedTime += deltaTime;

	float normalizedElapsedTime = _elapsedTime / _duration;
	float opacityValue = _opacityCurve->GetFloatValue(normalizedElapsedTime);
	UWidget* widget = GetWidget();

	if(widget)
	{
		widget->SetRenderOpacity(opacityValue);
	}

	if (_elapsedTime > _duration)
	{
		SetProcessSucceed();
	}
}


void UFlickeringUIProcess::VOnDead()
{
	Super::VOnDead();

	_elapsedTime = 0;
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
