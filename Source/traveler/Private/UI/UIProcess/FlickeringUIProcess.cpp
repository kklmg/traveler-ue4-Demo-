// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIProcess/FlickeringUIProcess.h"

void UFlickeringUIProcess::VTMInitialize()
{
	Super::VTMInitialize();
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


bool UFlickeringUIProcess::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;

	return (_opacityCurve && _duration > 0.0f);
}

void UFlickeringUIProcess::VTMExecute()
{
	Super::VTMExecute();

}

void UFlickeringUIProcess::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

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
		SetSucceed();
	}
}

void UFlickeringUIProcess::VTMReset()
{
	Super::VTMReset();
}

void UFlickeringUIProcess::VTMOnDead()
{
	Super::VTMOnDead();

	_elapsedTime = 0;
}

void UFlickeringUIProcess::VTMOnSucceed()
{
	Super::VTMOnSucceed();
}

void UFlickeringUIProcess::VTMOnFailed()
{
	Super::VTMOnFailed();
}

void UFlickeringUIProcess::VTMOnAborted()
{
	Super::VTMOnAborted();
}
