// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessBase.h"

void UProcessBase::Init()
{
	if (IsAlive())
	{
		SetProcessAborted();
	}

	SetProcessState(EProcessState::EPS_ReadyToExecute);
	VOnInit();
}

bool UProcessBase::Execute()
{
	if (VCanExecute() && SetProcessState(EProcessState::EPS_Running))
	{
		VOnExecute();

		if (_bIsInstantProcess)
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
		VOnSucceed();
		VOnDead();
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
		VOnFailed();
		VOnDead();
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
		VOnAborted();
		VOnDead();
		return true;
	}
	else
	{
		return false;
	}
}

bool UProcessBase::SetProcessState(EProcessState newState)
{
	if (_processState == newState) return false;

	_processState = newState;
	ProcessStateChangedDelegate.Broadcast(_processState);

	return true;
}

void UProcessBase::Tick(float deltaTime)
{
	if (_processState == EProcessState::EPS_Running)
	{
		VOnTick(deltaTime);
	}
}

bool UProcessBase::IsAlive()
{
	return (_processState == EProcessState::EPS_Running || _processState == EProcessState::EPS_Paused);
}

bool UProcessBase::IsDead()
{
	return (_processState == EProcessState::EPS_SUCCEEDED || _processState == EProcessState::EPS_FAILED || _processState == EProcessState::EPS_Aborted);
}

EProcessState UProcessBase::GetProcessState()
{
	return _processState;
}

bool UProcessBase::IsInstantProcess()
{
	return _bIsInstantProcess;
}

FName UProcessBase::GetProcessName()
{
	return _processName;
}


//Internal Functions -----------------------------------

void UProcessBase::VOnInit()
{
}

void UProcessBase::VOnExecute()
{
}

void UProcessBase::VOnTick(float deltaTime)
{
}

void UProcessBase::VOnDead()
{
}

void UProcessBase::VOnSucceed()
{
}

void UProcessBase::VOnFailed()
{
}

void UProcessBase::VOnAborted()
{
}