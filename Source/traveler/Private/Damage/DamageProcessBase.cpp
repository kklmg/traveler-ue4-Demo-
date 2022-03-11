// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/DamageProcessBase.h"
#include "Components/DamageHandlerComponent.h"
#include "Interface/AttributeInterface.h"


void UDamageProcessBase::SetData(AActor* actor, UMyDamageType* damageType, AMyHUD* hud)
{
	_damageType = damageType;
	_damageReceiver = actor;
	_hud = hud;
	_attributeInterface = Cast<IAttributeInterface>(actor);
}

bool UDamageProcessBase::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;

	return (_damageType && _attributeInterface);
}

void UDamageProcessBase::VTMExecute()
{
	if (_damageType)
	{
		_damageRemainCount = _damageType->DamageHandleCount;
		_damageInterval = _damageType->DamageHandleInterval;
	}
}

FName UDamageProcessBase::VGetProcessName()
{
	return _damageType ? _damageType->GetDamageTypeName() : FName(TEXT("UnKnown"));
}

bool UDamageProcessBase::VIsInstantProcess()
{
	return _damageType ? _damageType->bIsContinuousDamage == false : true;
}

void UDamageProcessBase::VTMTick(float deltaTime)
{
	_elapsedTime += deltaTime;

	while (_elapsedTime > _damageInterval && _damageRemainCount > 0)
	{
		_elapsedTime -= _damageInterval;
		_damageRemainCount--;

		_attributeInterface->VSetAttributeChange(EAttributeType::EATT_Health, -_damageType->BasicDamage);

		//show damage om screen
		if(_hud)
		{
			FDamageDisplayData damageDisplayData;
			damageDisplayData.Damage = _damageType->BasicDamage;
			damageDisplayData.DamageType = _damageType->DamageType;
			damageDisplayData.Location = _damageReceiver->GetActorLocation();

			_hud->ShowDamage(damageDisplayData);
		}
	}

	if (_damageRemainCount <= 0)
	{
		SetSucceed();
	}
}

void UDamageProcessBase::VTMOnDead()
{
	_elapsedTime = 0;
}

void UDamageProcessBase::VTMReset()
{

}
