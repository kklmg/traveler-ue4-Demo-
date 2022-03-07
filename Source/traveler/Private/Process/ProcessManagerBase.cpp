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
		TScriptInterface<IProcessInterface> process = _processesStorage[processName];
		process->VInitialize();

		if(process->VCanExecute())
		{
			process->VExecute();

			if (process->VIsInstantProcess() == false)
			{
				_runningProcesses.Add(process->VGetProcessName(), process);
			}

			FString logString(TEXT("Execute Process: "));
			logString.Append(processName.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, logString);
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
		_runningProcesses[processName]->VAbort();
		_runningProcesses.Remove(processName);

		FString logString(TEXT("Stop Process: "));
		logString.Append(processName.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, logString);
	}

}

void UProcessManagerBase::StopAllProcess()
{
	for (TPair<FName, TScriptInterface<IProcessInterface>> processElement : _runningProcesses)
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
		TScriptInterface<IProcessInterface> processInterface;
		processInterface.SetInterface(process);
		processInterface.SetObject(Cast<UObject>(process));

		_processesStorage.Add(process->VGetProcessName(), processInterface);
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
	for(TPair<FName, TScriptInterface<IProcessInterface>> processElement : _runningProcesses)
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
