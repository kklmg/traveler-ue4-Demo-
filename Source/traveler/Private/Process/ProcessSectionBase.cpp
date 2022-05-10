// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessSectionBase.h"

void UProcessSectionBase::SetDuration(float duration)
{
	_duration = duration;
}

float UProcessSectionBase::GetElapsedTime()
{
	return _elapsedTime;
}

void UProcessSectionBase::VTMInitialize()
{
	Super::VOnInit();
	_elapsedTime = 0;
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

	_elapsedTime += deltaTime;

	if (_elapsedTime > _duration)
	{
		SetProcessSucceed();
	}
}


void UProcessSectionBase::VOnDead()
{
	Super::VOnDead();

	_elapsedTime = 0;
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
