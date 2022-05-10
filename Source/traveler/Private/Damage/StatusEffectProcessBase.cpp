// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/StatusEffectProcessBase.h"
#include "Components/DamageHandlerComponent.h"
#include "Components/ActorUIComponent.h"
#include "Components/EffectControllerComponent.h"
#include "Components/DamageHandlerComponent.h"
#include "Damage/DamageHandlerInterface.h"
#include "GameSystem/MyGameplayStatics.h"



void UStatusEffectProcessBase::SetData(AActor* effectReceiver, AActor* effectCauser, APawn* effectInstigator, UStatusEffectData* effectData)
{
	check(effectReceiver);

	_effectReceiver = effectReceiver;
	_effectCauser = effectCauser;
	_effectInstigator = effectInstigator;

	_actorUIComp = Cast<UActorUIComponent>(effectReceiver->GetComponentByClass(UActorUIComponent::StaticClass()));
	_effectControlComp = Cast<UEffectControllerComponent>(effectReceiver->GetComponentByClass(UEffectControllerComponent::StaticClass()));
	_damageHandlerComp = Cast<UDamageHandlerComponent>(effectReceiver->GetComponentByClass(UDamageHandlerComponent::StaticClass()));

	if(effectData)
	{
		_damage = effectData->Damage;
		_damageInterval = effectData->DamageInterval;
		_effectDuration = effectData->EffectDuration;
		_elementalType = effectData->ElementalType;
		_statusEffectType = effectData->StatusEffectType;
	}
}

void UStatusEffectProcessBase::VOnInit()
{
	Super::VOnInit();

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

	if (_actorUIComp)
	{
		_actorUIComp->ShowActorStatusEffectUI(_statusEffectType, _effectDuration);
	}
}

bool UStatusEffectProcessBase::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	if (_effectDuration <= 0.0f) return false;
   
	return true;
}

void UStatusEffectProcessBase::VOnExecute()
{
	if (_actorUIComp)
	{
		_actorUIComp->ShowActorStatusEffectUI(_statusEffectType, _effectDuration);
	}

	if(_effectControlComp)
	{
		_effectControlComp->PlayEffect(EEffectType::EEffectType_StatusEffect, (uint8)_statusEffectType);
	}
}

void UStatusEffectProcessBase::VOnTick(float deltaTime)
{
	_totalElapsedTime += deltaTime;
	_ElapsedTimeFromLastDamage += deltaTime;


	while (_ElapsedTimeFromLastDamage >= _damageInterval)
	{
		if (_damage != 0.0f && _damageHandlerComp)
		{
			_damageHandlerComp->HandleDamage(_damage, _elementalType, _effectReceiver->GetActorLocation(),
				_effectCauser, _effectInstigator);
		}


		_ElapsedTimeFromLastDamage -= _damageInterval;
	}


	if (_totalElapsedTime > _effectDuration)
	{
		SetProcessSucceed();
	}
}

void UStatusEffectProcessBase::VOnDead()
{
	if(_actorUIComp)
	{
		_actorUIComp->HideActorStatusEffectUI(_statusEffectType);
	}
	if (_effectControlComp)
	{
		_effectControlComp->StopEffect(EEffectType::EEffectType_StatusEffect, (uint8)_statusEffectType);
	}
}