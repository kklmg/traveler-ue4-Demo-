// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessBase.h"

void UProcessBase::VInitialize()
{
	_processState = EProcessState::EPS_ReadyToExecute;
	VTMInitialize();
}

void UProcessBase::VExecute()
{
	if (_processState == EProcessState::EPS_ReadyToExecute && VTMCanExecute())
	{
		_processState = EProcessState::EPS_Running;
		VTMExecute();
	}
}

void UProcessBase::VTick(float deltaTime)
{
	if (_processState == EProcessState::EPS_Running)
	{
		VTMTick(deltaTime);
	}
}

void UProcessBase::VAbort()
{
	if (VIsAlive())
	{
		_processState = EProcessState::EPS_Aborted;
		VTMOnDead();
	}
}


void UProcessBase::VReset()
{
	_processState = EProcessState::EPS_UnInitialized;
	VTMReset();
}

void UProcessBase::VTMInitialize()
{
}

bool UProcessBase::VTMCanExecute()
{
	return true;
}

void UProcessBase::VTMExecute()
{
}

void UProcessBase::VTMTick(float deltaTime)
{
}

void UProcessBase::VTMOnDead()
{
}

void UProcessBase::VTMOnSucceed()
{
}

void UProcessBase::VTMOnFailed()
{
}

void UProcessBase::VTMOnAborted()
{
}

void UProcessBase::VTMReset()
{
}

void UProcessBase::SetSucceed()
{
	if(_processState == EProcessState::EPS_Running)
	{
		_processState = EProcessState::EPS_SUCCEEDED;
		VTMOnSucceed();
	}
}

void UProcessBase::SetFailed()
{
	if (_processState == EProcessState::EPS_Running)
	{
		_processState = EProcessState::EPS_FAILED;
		VTMOnFailed();
	}
}


bool UProcessBase::VIsAlive()
{
	return (_processState == EProcessState::EPS_Running || _processState == EProcessState::EPS_Paused);
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