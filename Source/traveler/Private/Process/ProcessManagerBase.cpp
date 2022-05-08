// Fill out your copyright notice in the Description page of Project Settings.


#include "Process/ProcessManagerBase.h"
#include "Process/ProcessBase.h"


void UProcessManagerBase::ExecuteProcess(UProcessBase* process)
{
	if (!process) return;

	if (_runningProcesses.Contains(process->GetProcessName()))
	{
		UE_LOG(LogTemp, Log, TEXT("the same process is running: %s"), *process->GetProcessName().ToString());
	}
	else
	{
		process->Init();
		if (process->VCanExecute())
		{
			process->Execute();

			if (process->IsInstantProcess() == false)
			{
				_runningProcesses.Add(process->GetProcessName(), process);
			}
		}
	}
}

void UProcessManagerBase::ExecutePresetedProcess(FName processName)
{
	if (_runningProcesses.Contains(processName))
	{
		UE_LOG(LogTemp, Log, TEXT("the same process is running: %s"), *processName.ToString());
	}
	else if (_processPresets.Contains(processName))
	{
		UProcessBase* process = _processPresets[processName];
		process->Init();

		if (process->VCanExecute())
		{
			process->Execute();

			if (process->IsInstantProcess() == false)
			{
				_runningProcesses.Add(process->GetProcessName(), process);
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT(" process cant be executed: %s"), *processName.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("no process instance: %s"), *processName.ToString());
	}
}

void UProcessManagerBase::StopProcess(FName processName)
{
	if (_runningProcesses.Contains(processName))
	{
		_runningProcesses[processName]->Abort();
		_runningProcesses.Remove(processName);

		FString logString(TEXT("Stop Process: "));
		logString.Append(processName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, logString);
	}
}

void UProcessManagerBase::StopAllProcess()
{
	for (TPair<FName, UProcessBase*> processElement : _runningProcesses)
	{
		processElement.Value->Abort();
	}

	_runningProcesses.Empty();
}

void UProcessManagerBase::AddToProcessPresets(UProcessBase* process)
{
	if (!process) return;

	if (_processPresets.Contains(process->GetProcessName()))
	{
		//_processesStorage[processName] = process;
		UE_LOG(LogTemp, Warning, TEXT("Try to add duplicated process!"));
	}
	else
	{
		_processPresets.Add(process->GetProcessName(), process);
	}
}

bool UProcessManagerBase::IsProcessRunning(FName processName)
{
	return _processPresets.Contains(processName) ?
		_processPresets[processName]->GetProcessState() == EProcessState::EPS_Running : false;
}

void UProcessManagerBase::Tick(float deltaTime)
{
	TArray<FName> deadProcesses;

	//Tick Processes
	for (TPair<FName, UProcessBase*> processElement : _runningProcesses)
	{
		processElement.Value->Tick(deltaTime);
		if (processElement.Value->IsDead())
		{
			deadProcesses.Add(processElement.Key);
		}
	}

	//Clear Dead Processes
	for (FName processName : deadProcesses)
	{
		_runningProcesses.Remove(processName);
	}
}
