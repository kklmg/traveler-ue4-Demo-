// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/StatusEffectProcessManager.h"
#include "Damage/StatusEffectProcessBase.h"
#include "Data/StatusEffectData.h"
#include "UI/MyHUD.h"


UStatusEffectProcessManager::UStatusEffectProcessManager()
{
}

void UStatusEffectProcessManager::ExecuteProcess(AActor* effectReceiver, AActor* effectCauser, APawn* effectInstigator, UStatusEffectData* statusEffectData)
{
	if (!statusEffectData) return;

	if (HandleElementalReaction(statusEffectData))
	{
	}
	else if (_processMap.Contains(statusEffectData->StatusEffectType))
	{
		_processMap[statusEffectData->StatusEffectType]->ApplyDurationChange(statusEffectData->EffectDuration);
	}
	else
	{
		UStatusEffectProcessBase* newProcess = NewObject<UStatusEffectProcessBase>(this);
		newProcess->SetData(effectReceiver, effectCauser, effectInstigator, statusEffectData);
		newProcess->Init();
		newProcess->Execute();
		_processMap.Add(statusEffectData->StatusEffectType, newProcess);
	}
}

UStatusEffectProcessBase* UStatusEffectProcessManager::StopProcess(EStatusEffect statusEffectType)
{
	if (_processMap.Contains(statusEffectType))
	{
		UStatusEffectProcessBase* process = _processMap[statusEffectType];
		process->Abort();
		 _processMap.Remove(statusEffectType);
		 return process;
	}

	return nullptr;
}

bool UStatusEffectProcessManager::IsExistStatusEffect(EStatusEffect statusEffectType)
{
	return _processMap.Contains(statusEffectType);
}

void UStatusEffectProcessManager::Tick(float deltaTime)
{
	static TArray<EStatusEffect> deadProcesstypes;

	//run processes
	for (auto processElement : _processMap)
	{
		processElement.Value->Tick(deltaTime);

		if(processElement.Value->IsDead())
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

bool UStatusEffectProcessManager::ApplyDurationChange(EStatusEffect statusEffectType, float deltaDuration)
{
	if (_processMap.Contains(statusEffectType)) 
	{
		_processMap[statusEffectType]->ApplyDurationChange(deltaDuration);
		if (_processMap[statusEffectType]->GetRemainingTime() <= 0.0f)
		{
			StopProcess(statusEffectType);
		}

		return true;
	}
	else
	{
		return false;
	}
}

//todo
bool UStatusEffectProcessManager::HandleElementalReaction(UStatusEffectData* statusEffectData)
{
	switch (statusEffectData->StatusEffectType)
	{
		case EStatusEffect::EStatusEffect_Fire:
		{
			if (ApplyDurationChange(EStatusEffect::EStatusEffect_Water, -statusEffectData->EffectDuration)) return true;
			if (ApplyDurationChange(EStatusEffect::EStatusEffect_Ice, -statusEffectData->EffectDuration * 0.5f)) return true;
		}
			break;
		case EStatusEffect::EStatusEffect_Water:
		{
			if (ApplyDurationChange(EStatusEffect::EStatusEffect_Fire, -statusEffectData->EffectDuration)) return true;
			if (ApplyDurationChange(EStatusEffect::EStatusEffect_Electricity, -statusEffectData->EffectDuration * 0.5f)) return true;
		}
			break;
		case EStatusEffect::EStatusEffect_Ice:
		{
			if (ApplyDurationChange(EStatusEffect::EStatusEffect_Fire, -statusEffectData->EffectDuration * 1.5f)) return true;
		}
			break;
		case EStatusEffect::EStatusEffect_Electricity:
		{
			if (ApplyDurationChange(EStatusEffect::EStatusEffect_Water, -statusEffectData->EffectDuration)) return true;
		}
			break;
		case EStatusEffect::EStatusEffect_Poison:
			break;
		case EStatusEffect::EStatusEffect_Stun:
			break;
		case EStatusEffect::EStatusEffect_Size:
			break;
		default: return false;
			break;
	}
	return false;
}
