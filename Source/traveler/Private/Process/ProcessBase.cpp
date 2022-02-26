// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessBase.h"

void UProcessBase::VEnter()
{
	_processState = EProcessState::EPS_Running;
	VTMEnter();
}

void UProcessBase::VTick(float deltaTime)
{
	if (_processState == EProcessState::EPS_Running)
	{
		VTMTick(deltaTime);
	}
}

void UProcessBase::VEnd()
{
	_processState = EProcessState::EPS_SUCCEEDED;
	VTMEnd();
}

void UProcessBase::VReset()
{
	_processState == EProcessState::EPS_ReadyToExecute;
	VTMReset();
}


bool UProcessBase::VIsAlive()
{
	return (_processState == EProcessState::EPS_Running || _processState == EProcessState::EPS_Running);
}
bool UProcessBase::VIsDead()
{
	return (_processState == EProcessState::EPS_SUCCEEDED || _processState == EProcessState::EPS_FAILED || _processState == EProcessState::EPS_Aborted);
}

EProcessState UProcessBase::VGetProcessState()
{
	return _processState;
}

void UProcessBase::VSetState(EProcessState newState)
{
	_processState = newState;
}