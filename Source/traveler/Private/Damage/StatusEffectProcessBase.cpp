// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/StatusEffectProcessBase.h"
#include "Components/DamageHandlerComponent.h"
#include "Interface/ActorUIInterface.h"
#include "Interface/ActorEffectInterface.h"
#include "Damage/DamageHandlerInterface.h"
#include "GameSystem/MyGameplayStatics.h"



void UStatusEffectProcessBase::SetData(AActor* effectReceiver, AActor* effectCauser, APawn* effectInstigator, UStatusEffectData* effectData)
{
	_effectReceiver = effectReceiver;
	_effectCauser = effectCauser;
	_effectInstigator = effectInstigator;

	_actorUIInterface = Cast<IActorUIInterface>(effectReceiver);
	_actorEffectInterface = Cast<IActorEffectInterface>(effectReceiver);
	_damageHandlerInterface = Cast<IDamageHandlerInterface>(effectReceiver);

	if(effectData)
	{
		_damage = effectData->Damage;
		_damageInterval = effectData->DamageInterval;
		_effectDuration = effectData->EffectDuration;
		_elementalType = effectData->ElementalType;
		_statusEffectType = effectData->StatusEffectType;
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
		_effectDuration = FMath::Max(_effectDuration, statusEffectData->EffectDuration);

		_totalElapsedTime = 0;
		_ElapsedTimeFromLastDamage = 0;
	}

	if (_actorUIInterface)
	{
		_actorUIInterface->VShowActorStatusUI(_statusEffectType, _effectDuration);
	}
}

bool UStatusEffectProcessBase::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;

	if (_effectDuration <= 0.0f) return false;
   
	return true;
}

void UStatusEffectProcessBase::VTMExecute()
{
	if (_actorUIInterface)
	{
		_actorUIInterface->VShowActorStatusUI(_statusEffectType, _effectDuration);
	}

	if(_actorEffectInterface)
	{
		_actorEffectInterface->VPlayEffect(_statusEffectType);
	}
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
		if (_damage != 0.0f && _damageHandlerInterface)
		{
			_damageHandlerInterface->VHandleDamage(_damage, _elementalType, _effectReceiver->GetActorLocation(), 
				_effectCauser, _effectInstigator);
		}


		_ElapsedTimeFromLastDamage -= _damageInterval;
	}


	if (_totalElapsedTime > _effectDuration)
	{
		SetSucceed();
	}
}

void UStatusEffectProcessBase::VTMOnDead()
{
	if(_actorUIInterface)
	{
		_actorUIInterface->VHideActorStatusUI(_statusEffectType);
	}
	if (_actorEffectInterface)
	{
		_actorEffectInterface->VStopEffect(_statusEffectType);
	}
}

void UStatusEffectProcessBase::VTMReset()
{
	
}
