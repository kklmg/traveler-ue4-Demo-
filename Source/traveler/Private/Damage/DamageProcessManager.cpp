// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/DamageProcessManager.h"
#include "Damage/StatusEffectProcessBase.h"
#include "Data/StatusEffectData.h"
#include "UI/MyHUD.h"


UDamageProcessManager::UDamageProcessManager()
{
}

void UDamageProcessManager::ExecuteProcess(AActor* owner, UStatusEffectData* statusEffectData)
{
	if (!statusEffectData) return;
	
	if (_processMap.Contains(statusEffectData->StatusEffectType))
	{
		_processMap[statusEffectData->StatusEffectType]->CombineEffectData(statusEffectData);
	}
	else
	{
		UStatusEffectProcessBase* newProcess = NewObject<UStatusEffectProcessBase>(this);
		newProcess->SetData(owner, statusEffectData);
		newProcess->VInitialize();
		newProcess->VExecute();
		_processMap.Add(statusEffectData->StatusEffectType, newProcess);
	}
}

UStatusEffectProcessBase* UDamageProcessManager::StopProcess(EStatusEffect statusEffectType)
{
	if (_processMap.Contains(statusEffectType))
	{
		UStatusEffectProcessBase* process = _processMap[statusEffectType];
		process->VAbort();
		 _processMap.Remove(statusEffectType);
		 return process;
	}

	return nullptr;
}

bool UDamageProcessManager::IsExistStatusEffect(EStatusEffect statusEffectType)
{
	return _processMap.Contains(statusEffectType);
}

void UDamageProcessManager::Tick(float deltaTime)
{
	static TArray<EStatusEffect> deadProcesstypes;

	//run processes
	for (auto processElement : _processMap)
	{
		processElement.Value->VTick(deltaTime);

		if(processElement.Value->VIsDead())
		{
			deadProcesstypes.Add(processElement.Key);
		}
	}

	//clear dead processes
	for(auto deadProcessType : deadProcesstypes)
	{
		_processMap.Remove(deadProcessType);
	}
	deadProcesstypes.Empty();
}
