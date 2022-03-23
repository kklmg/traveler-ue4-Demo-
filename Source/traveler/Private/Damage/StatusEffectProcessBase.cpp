// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/StatusEffectProcessBase.h"
#include "Components/DamageHandlerComponent.h"
#include "Interface/ActorUIInterface.h"



void UStatusEffectProcessBase::SetData(AActor* effectReceiver, UStatusEffectData* effectData)
{
	effectReceiver = _effectReceiver;
	_UIInterface = Cast<IActorUIInterface>(effectReceiver);

	if(effectData)
	{
		_damage = effectData->Damage;
		_damageInterval = effectData->DamageInterval;
		_damageDuration = effectData->DamageDuration;
		_statusEffectType = effectData->StatusEffectType;
		_effectActorClass = effectData->EffectActorClass;
	}
}

void UStatusEffectProcessBase::VTMInitialize()
{
	Super::VTMInitialize();

	_totalElapsedTime = 0;
	_ElapsedTimeFromLastDamage = 0;
}


void UStatusEffectProcessBase::CombineEffectData(UStatusEffectData* statusEffectData)
{
	if (statusEffectData)
	{
		_damage = FMath::Max(_damage, statusEffectData->Damage);
		_damageInterval = FMath::Min(_damageInterval, statusEffectData->DamageInterval);
		_damageDuration = FMath::Max(_damageDuration, statusEffectData->DamageDuration);

		_statusEffectType = statusEffectData->StatusEffectType;

		_effectActorClass = statusEffectData->EffectActorClass;

		_totalElapsedTime = 0;
		_ElapsedTimeFromLastDamage = 0;
	}
}

bool UStatusEffectProcessBase::VTMCanExecute()
{
	if (!VTMCanExecute()) return false;

	if (_damageDuration <= 0.0f) return false;
   
	return true;
}

void UStatusEffectProcessBase::VTMExecute()
{
	//_UIInterface->VShowActorStatusUI(EActorStatus,_damageDuration)
	//SpawnEffectActor();
}

bool UStatusEffectProcessBase::VIsInstantProcess()
{
    return false;
}

void UStatusEffectProcessBase::VTMTick(float deltaTime)
{
	_totalElapsedTime += deltaTime;
	_ElapsedTimeFromLastDamage += deltaTime;


	while (_ElapsedTimeFromLastDamage >= _damageInterval)
	{
		//_damageHandler->HandleDamage();
		_ElapsedTimeFromLastDamage -= _damageInterval;
	}


	if (_totalElapsedTime > _damageDuration)
	{
		SetSucceed();
	}
}

void UStatusEffectProcessBase::VTMOnDead()
{
	if(_attributeInterface)
	{
		
	}
}

void UStatusEffectProcessBase::VTMReset()
{
	
}

void UStatusEffectProcessBase::SpawnEffectActor()
{
}

void UStatusEffectProcessBase::DestroyEffectActor()
{
}
