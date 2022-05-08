// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessBase.h"

void UProcessBase::Init()
{
	if (IsAlive())
	{
		SetProcessAborted();
	}

	SetProcessState(EProcessState::EPS_ReadyToExecute);
	VTMInit();
}

bool UProcessBase::Execute()
{
	if (VCanExecute() && SetProcessState(EProcessState::EPS_Running))
	{
		VTMExecute();

		if(_bIsInstantProcess)
		{
			SetProcessSucceed();
		}

		return true;
	}
	else
	{
		SetProcessFailed();
		return false;
	}
}

bool UProcessBase::Abort()
{
	return SetProcessAborted();
}

bool UProcessBase::VCanExecute()
{
	return _processState == EProcessState::EPS_ReadyToExecute;
}

bool UProcessBase::SetProcessSucceed()
{
	if (IsAlive() && SetProcessState(EProcessState::EPS_SUCCEEDED))
	{
		VTMOnSucceed();
		VTMOnDead();
		return true;
	}
	else
	{
		return false;
	}
}

bool UProcessBase::SetProcessFailed()
{
	if (IsAlive() && SetProcessState(EProcessState::EPS_FAILED))
	{
		VTMOnFailed();
		VTMOnDead();
		return true;
	}
	else
	{
		return false;
	}
}

bool UProcessBase::SetProcessAborted()
{
	if (IsAlive() && SetProcessState(EProcessState::EPS_Aborted))
	{
		VTMOnAborted();
		VTMOnDead();
		return true;
	}
	else
	{
		return false;
	}
}

FORCEINLINE_DEBUGGABLE bool UProcessBase::SetProcessState(EProcessState newState)
{
	if (_processState == newState) return false;

	_processState = newState;
	ProcessStateChangedDelegate.Broadcast(_processState);

	return true;
}

FORCEINLINE_DEBUGGABLE void UProcessBase::Tick(float deltaTime)
{
	if (_processState == EProcessState::EPS_Running)
	{
		VTMTick(deltaTime);
	}
}

FORCEINLINE_DEBUGGABLE bool UProcessBase::IsAlive()
{
	return (_processState == EProcessState::EPS_Running || _processState == EProcessState::EPS_Paused);
}

FORCEINLINE_DEBUGGABLE bool UProcessBase::IsDead()
{
	return (_processState == EProcessState::EPS_SUCCEEDED || _processState == EProcessState::EPS_FAILED || _processState == EProcessState::EPS_Aborted);
}

FORCEINLINE_DEBUGGABLE EProcessState UProcessBase::GetProcessState()
{
	return _processState;
}

FORCEINLINE_DEBUGGABLE bool UProcessBase::IsInstantProcess()
{
	return _bIsInstantProcess;
}

FORCEINLINE_DEBUGGABLE FName UProcessBase::GetProcessName()
{
	return _processName;
}


//Internal Functions -----------------------------------

void UProcessBase::VTMInit()
{
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