// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessManagerBase.h"

void UProcessManagerBase::ExecuteProcess(FName processName)
{	
	if(_runningProcesses.Contains(processName))
	{
		UE_LOG(LogTemp, Log, TEXT("the same process is running: %s"),*processName.ToString());
	}
	else if (_processesStorage.Contains(processName))
	{
		IProcessInterface* process = _processesStorage[processName];
		process->VInitialize();
		process->VExecute();
		
		_runningProcesses.Add(process->VGetProcessName(),process);
	}

	UE_LOG(LogTemp, Log, TEXT("no process instance: %s"), *processName.ToString());
}

void UProcessManagerBase::StopProcess(FName processName)
{
	if (_runningProcesses.Contains(processName))
	{
		_runningProcesses[processName]->VAbort();
		_runningProcesses.Remove(processName);
	}

}

void UProcessManagerBase::StopAllProcess()
{
	for (TPair<FName, IProcessInterface*> processElement : _runningProcesses)
	{
		processElement.Value->VAbort();
	}

	_runningProcesses.Empty();
}

void UProcessManagerBase::AddProcess(IProcessInterface* process)
{
	if (!process) return;

	if (_processesStorage.Contains(process->VGetProcessName()))
	{
		//_processesStorage[processName] = process;
		UE_LOG(LogTemp, Warning, TEXT("Try to add duplicated process!"));
	}
	else
	{
		_processesStorage.Add(process->VGetProcessName(), process);
	}

}

EProcessState UProcessManagerBase::GetProcessState(FName processName)
{
	if (_processesStorage.Contains(processName))
	{
		return _processesStorage[processName]->VGetProcessState();
	}
	return EProcessState::EPS_None;
}

void UProcessManagerBase::Tick(float deltaTime)
{
	TArray<FName> deadProcesses;

	//Tick Processes
	for(TPair<FName, IProcessInterface*> processElement : _runningProcesses)
	{
		processElement.Value->VTick(deltaTime);
		if (processElement.Value->VIsDead())
		{
			deadProcesses.Add(processElement.Key);
		}
	}

	//Clear Dead Processes
	for(FName processName : deadProcesses)
	{
		_runningProcesses.Remove(processName);
	}
}
