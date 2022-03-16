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
	Super::VTMInitialize();
	_elapsedTime = 0;
}

bool UProcessSectionBase::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;

	return true;
}

void UProcessSectionBase::VTMExecute()
{
	Super::VTMExecute();
}

void UProcessSectionBase::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	_elapsedTime += deltaTime;

	if (_elapsedTime > _duration)
	{
		SetSucceed();
	}
}

void UProcessSectionBase::VTMReset()
{
	Super::VTMReset();

	_elapsedTime = 0;
}

void UProcessSectionBase::VTMOnDead()
{
	Super::VTMOnDead();

	_elapsedTime = 0;
}

void UProcessSectionBase::VTMOnSucceed()
{
	Super::VTMOnSucceed();
}

void UProcessSectionBase::VTMOnFailed()
{
	Super::VTMOnFailed();
}

void UProcessSectionBase::VTMOnAborted()
{
	Super::VTMOnAborted();
}
