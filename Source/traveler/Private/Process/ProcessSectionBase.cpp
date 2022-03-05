// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessSectionBase.h"

void UProcessSectionBase::VTMEnter()
{
	Super::VExecute();
}

void UProcessSectionBase::VTMTick(float deltaTime)
{
	Super::VTick(deltaTime);
	
	_elapsedTime += deltaTime;
}

//void UProcessSectionBase::VTMEnd()
//{
//	Super::VEnd();
//}

float UProcessSectionBase::GetElapsedTime()
{
	return _elapsedTime;
}

void UProcessSectionBase::VTMReset()
{
	_elapsedTime = 0;
}
