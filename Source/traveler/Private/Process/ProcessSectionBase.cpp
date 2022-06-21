// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessSectionBase.h"

void UProcessSectionBase::SetDuration(float duration)
{
	_duration = duration;
	_remainingTime= _duration;
}

float UProcessSectionBase::GetRemainingTime()
{
	return _remainingTime;
}

void UProcessSectionBase::VOnInitialized()
{
	Super::VOnInit();
	_remainingTime = _duration;
}

bool UProcessSectionBase::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	return true;
}

void UProcessSectionBase::VOnExecute()
{
	Super::VOnExecute();
}

void UProcessSectionBase::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	_remainingTime -= deltaTime;

	if (_remainingTime <0.0f)
	{
		SetProcessSucceed();
	}
}


void UProcessSectionBase::VOnDead()
{
	Super::VOnDead();
}

void UProcessSectionBase::VOnSucceed()
{
	Super::VOnSucceed();
}

void UProcessSectionBase::VOnFailed()
{
	Super::VOnFailed();
}

void UProcessSectionBase::VOnAborted()
{
	Super::VOnAborted();
}
