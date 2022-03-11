// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/DamageProcessManager.h"
#include "Damage/DamageProcessBase.h"
#include "UI/MyHUD.h"


UDamageProcessManager::UDamageProcessManager()
{
	_poolSize = 100;
}

void UDamageProcessManager::ExecuteProcess(UDamageProcessBase* process)
{
	if (!process) return;

	//Handle instant process
	if(process->VIsInstantProcess())
	{
		process->VInitialize();
		if(process->VCanExecute())
		{
			process->VExecute();	
		}

		return;
	}

	//check whether free pool slot is available
	if (_emptyIndicies.Num() == 0 && _runningProcesses.Num() == _poolSize)
	{
		UE_LOG(LogTemp,Warning,TEXT("no avaialable slot for new Damage process"));
		return;
	}

	//execute process
	process->VInitialize();
	if(process->VCanExecute()==false)
	{
		return;
	}
	process->VExecute();

	//add to process pool
	//---------------------------------------------------------------------

	//if emptyslot is available
	if (_emptyIndicies.Num() > 0)
	{
		uint32 emptySlotIndex = _emptyIndicies.Pop();
		_runningProcesses[emptySlotIndex] = process;
	}
	//
	else
	{
		_runningProcesses.Add(process);
	}
}

void UDamageProcessManager::Tick(float deltaTime)
{
	for (int32 i = 0; i < _runningProcesses.Num(); ++i)
	{
		//skip dead process
		if(_runningProcesses[i]->VIsDead())
		{
			continue;
		}

		//tick process
		_runningProcesses[i]->VTick(deltaTime);

		//mark dead processes
		if (_runningProcesses[i]->VIsDead())
		{
			_emptyIndicies.Add(i);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red,"Process pool num: "+ FString::FromInt(_runningProcesses.Num()));
}
