// Fill out your copyright notice in the Description page of Project Settings.


#include "Process.h"

UProcess::UProcess(void)
{
}

void UProcess::VInit(void) {}
void UProcess::VUpdate(unsigned long deltaMs) {}
void UProcess::VSuccess(void) {}
void UProcess::VFail(void) {}
void UProcess::VAbort(void) {}


// accessors
EProcessState UProcess::GetState(void) const
{ 
	return _state;
}
bool UProcess::IsAlive(void) const 
{
	return (_state == RUNNING || _state == PAUSED); 
}
bool UProcess::IsDead(void) const 
{
	return (_state == SUCCEEDED || _state == FAILED || _state == ABORTED); 
}
bool UProcess::IsPaused(void) const 
{ 
	return _state == PAUSED;
}

// child functions
inline void UProcess::AttachChild(UProcess *pChild) 
{
	_pChild = pChild;
}

UProcess* UProcess::RemoveChild(void)
{
	UProcess* process = _pChild;
	_pChild = nullptr;
	return process;
} 
UProcess* UProcess::PeekChild(void)
{
	return _pChild;
}

void UProcess::SetState(EProcessState newState) 
{ 
	_state = newState; 
}