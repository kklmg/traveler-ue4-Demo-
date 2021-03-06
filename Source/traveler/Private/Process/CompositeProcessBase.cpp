// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/CompositeProcessBase.h"


UCompositeProcessBase::UCompositeProcessBase()
{
}

void UCompositeProcessBase::AddProcess(UProcessBase* process)
{
	_procesPool.Add(process);
}


void UCompositeProcessBase::setIsLoop(bool isLoop)
{
	_bLoop = isLoop;
}

void UCompositeProcessBase::VOnInit()
{
	Super::VOnInit();

    for (UProcessBase* process : _procesPool)
    {
        if (process)
        {
            process->Init();
        }
    }

    _curProcessID = 0;
	_procesPool[_curProcessID]->Init();
}

bool UCompositeProcessBase::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	if (_curProcessID >= _procesPool.Num()) return false;

	return 	_procesPool[_curProcessID]->VCanExecute();
}

void UCompositeProcessBase::VOnExecute()
{
	_procesPool[_curProcessID]->Execute();
}

void UCompositeProcessBase::VOnTick(float deltaTime)
{
    _procesPool[_curProcessID]->Tick(deltaTime);

    //current process is finshed
    if(_procesPool[_curProcessID]->IsDead())
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
                SetProcessSucceed();
				return;
            }
        }

        //execute next process
        _procesPool[_curProcessID]->Init();
        _procesPool[_curProcessID]->Execute();
    }
}

void UCompositeProcessBase::VOnDead()
{
	Super::VOnDead();
}

void UCompositeProcessBase::VOnAborted()
{
	Super::VOnAborted();

    for (UProcessBase* process : _procesPool)
    {
        if (process)
        {
			process->Abort();
        }
    }
}

