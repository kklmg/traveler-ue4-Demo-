// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessManager.h"



UProcessManager::UProcessManager()
{

}

unsigned int UProcessManager::UpdateProcesses(unsigned long deltaMs)
{
    unsigned short int successCount = 0;
    unsigned short int failCount = 0;

   for(auto pProcess : _processList)
   {
        // process is uninitialized, so initialize it
        if (pProcess->GetState() == EProcessState::UNINITIALIZED)
            pProcess->VInit();

        // give the process an update tick if it's running
        if (pProcess->GetState() == EProcessState::RUNNING)
            pProcess->VUpdate(deltaMs);

        // check to see if the process is dead
        if (pProcess->IsDead())
        {
            // run the appropriate exit function
            switch (pProcess->GetState())
            {
            case EProcessState::SUCCEEDED:
            {
                pProcess->VSuccess();
                UProcess* pChild = pProcess->RemoveChild();
                if (pChild)
                    AddProcess(pChild);
                else
                    ++successCount;  // only counts if the whole chain completed
                break;
            }

            case EProcessState::FAILED:
            {
                pProcess->VFail();
                ++failCount;
                break;
            }

            case EProcessState::ABORTED:
            {
                pProcess->VAbort();
                ++failCount;
                break;
            }
            }

            // remove the process
            _processList.Remove(pProcess);
        }
   }

    return ((successCount << 16) | failCount);
}
void UProcessManager::AddProcess(UProcess* pProcess)
{
	_processList.Add(pProcess);
}
void UProcessManager::AbortAllProcesses()
{
    for (auto pProcess : _processList)
    {
        if (pProcess->IsAlive())
        {
            pProcess->SetState(EProcessState::ABORTED);
        }
    }
}

// accessors
int32 UProcessManager::GetProcessCount(void) const 
{ 
	return _processList.Num();
}

void UProcessManager::ClearAllProcesses(void)
{
	_processList.Empty();
}
