// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessBase.h"

void UProcessBase::VInitialize()
{
	if (VSetProcessState(EProcessState::EPS_ReadyToExecute))
	{
		VTMInitialize();
	}
}

bool UProcessBase::VExecute()
{
	if (VCanExecute() && VSetProcessState(EProcessState::EPS_Running))
	{
		VTMExecute();
		return true;
	}
	else
	{
		return false;
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
	if (VIsAlive() && VSetProcessState(EProcessState::EPS_Aborted))
	{
		VTMOnDead();
	}
}


void UProcessBase::VReset()
{
	if(VSetProcessState(EProcessState::EPS_UnInitialized))
	{
		VTMReset();
	}	
}

void UProcessBase::VTMInitialize()
{
}

bool UProcessBase::VCanExecute()
{
	return _processState == EProcessState::EPS_ReadyToExecute && VTMCanExecute();
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
	if(_processState == EProcessState::EPS_Running && VSetProcessState(EProcessState::EPS_SUCCEEDED))
	{
		VTMOnSucceed();
		VTMOnDead();
	}
}

void UProcessBase::SetFailed()
{
	if (_processState == EProcessState::EPS_Running && VSetProcessState(EProcessState::EPS_FAILED))
	{
		VTMOnFailed();
		VTMOnDead();
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

bool UProcessBase::VSetProcessState(EProcessState newState)
{
	if (newState == _processState) return false;

	_processState = newState;
	OnProcessStateChanged.Broadcast(_processState);

	return true;
}

bool UProcessBase::VIsInstantProcess()
{
	return false;
}


//FName UProcessBase::VGetProcessName()
//{
//	return FName();
//}
