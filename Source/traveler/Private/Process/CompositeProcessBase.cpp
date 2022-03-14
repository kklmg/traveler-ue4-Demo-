// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/CompositeProcessBase.h"


void UCompositeProcessBase::AddProcess(UProcessBase* process)
{
	_procesPool.Add(process);
}


void UCompositeProcessBase::VTMInitialize()
{
	Super::VTMInitialize();

    for (UProcessBase* process : _procesPool)
    {
        if (process) 
        {
			process->VInitialize();
        }
    }
    _curProcessID = 0;
}

bool UCompositeProcessBase::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;

	if (_procesPool.Num() == 0) return false;

    for(UProcessBase* process : _procesPool)
    {
		if (!process) return false;
		if (!process->VCanExecute()) return false;
    }

	return true;
}

void UCompositeProcessBase::VTMExecute()
{
    _curProcessID = 0;
	_procesPool[_curProcessID]->VExecute();
}

FName UCompositeProcessBase::VGetProcessName()
{
	return _processName;
}

bool UCompositeProcessBase::VIsInstantProcess()
{
    return false;
}

void UCompositeProcessBase::VTMTick(float deltaTime)
{
    _procesPool[_curProcessID]->VTick(deltaTime);

    //current process is finshed
    if(_procesPool[_curProcessID]->VIsDead())
    {
        //move index
		++_curProcessID;
        
        //no next process 
		if (_curProcessID >= _procesPool.Num())
        {
			SetSucceed();
        }
        //execute next process
        else
        {
            _procesPool[_curProcessID]->VExecute();
        }
    }
}

void UCompositeProcessBase::VTMOnDead()
{
	Super::VTMOnDead();
}

void UCompositeProcessBase::VTMOnAborted()
{
	Super::VTMOnAborted();

    for (UProcessBase* process : _procesPool)
    {
        if (process)
        {
			process->VAbort();
        }
    }

}

void UCompositeProcessBase::VTMReset()
{
    Super::VTMOnDead();
}
