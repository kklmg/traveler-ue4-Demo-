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
	Super::VTMInit();
	_elapsedTime = 0;
}

bool UProcessSectionBase::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

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
		SetProcessSucceed();
	}
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
