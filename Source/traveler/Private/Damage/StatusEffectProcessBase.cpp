// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/StatusEffectProcessBase.h"
#include "Components/DamageHandlerComponent.h"
#include "Interface/ActorUIInterface.h"
#include "Damage/DamageHandlerInterface.h"
#include "GameSystem/MyGameplayStatics.h"



void UStatusEffectProcessBase::SetData(AActor* effectReceiver, AActor* effectCauser, UStatusEffectData* effectData)
{
	_effectReceiver = effectReceiver;
	_effectCauser = effectCauser;
	_actorUIInterface = Cast<IActorUIInterface>(effectReceiver);
	_damageHandlerInterface = Cast<IDamageHandlerInterface>(effectReceiver);

	if(effectData)
	{
		_damage = effectData->Damage;
		_damageInterval = effectData->DamageInterval;
		_effectDuration = effectData->EffectDuration;
		_damageType = UMyGameplayStatics::StatusEffectTypeToDamageType(effectData->StatusEffectType);
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
		_effectDuration = FMath::Max(_effectDuration, statusEffectData->EffectDuration);

		_statusEffectType = statusEffectData->StatusEffectType;
		_effectActorClass = statusEffectData->EffectActorClass;

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

	if(_effectActorClass)
	{
		if(_effectActorIns)
		{
			_effectActorIns->Destroy();
			_effectActorIns = nullptr;
		}

		_effectActorIns = NewObject<AActor>(this, _effectActorClass);
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
			_damageHandlerInterface->VHandleDamage(_damage, _damageType, _effectReceiver->GetActorLocation(), _effectCauser);
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
	if(_effectActorIns)
	{
		_effectActorIns->Destroy();
		_effectActorIns = nullptr;
	}
}

void UStatusEffectProcessBase::VTMReset()
{
	
}
