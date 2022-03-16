// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/CompositeProcessBase.h"


void UCompositeProcessBase::AddProcess(UProcessBase* process)
{
	_procesPool.Add(process);
}


void UCompositeProcessBase::setIsLoop(bool isLoop)
{
	_bLoop = isLoop;
}

void UCompositeProcessBase::VTMInitialize()
{
	Super::VTMInitialize();

    _curProcessID = 0;
	_procesPool[_curProcessID]->VInitialize();
}

bool UCompositeProcessBase::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;

	if (_curProcessID >= _procesPool.Num()) return false;

	return 	_procesPool[_curProcessID]->VCanExecute();
}

void UCompositeProcessBase::VTMExecute()
{
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
        if(_bLoop)
        {
			_curProcessID = (_curProcessID + 1) % _procesPool.Num();
        }
        else
        {
			++_curProcessID;

            //no next process 
            if (_curProcessID >= _procesPool.Num())
            {
                SetSucceed();
				return;
            }
        }

        //execute next process
        _procesPool[_curProcessID]->VInitialize();
        _procesPool[_curProcessID]->VExecute();
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
