// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/StatusEffectProcessBase.h"
#include "Components/DamageHandlerComponent.h"
#include "Interface/AttributeInterface.h"
#include "Interface/ActorUIInterface.h"


void UStatusEffectProcessBase::SetData(AActor* effectReceiver, AMyHUD* hud)
{
	effectReceiver = _effectReceiver;
	_hud = hud;
	_attributeInterface = Cast<IAttributeInterface>(effectReceiver);
	_UIInterface = Cast<IActorUIInterface>(effectReceiver);
}

bool UStatusEffectProcessBase::VTMCanExecute()
{
	if (!VTMCanExecute()) return false;
   

	return true;
}

void UStatusEffectProcessBase::VTMExecute()
{
	

}

FName UStatusEffectProcessBase::VGetProcessName()
{
	return _effectName;
}

bool UStatusEffectProcessBase::VIsInstantProcess()
{
    return false;
}

void UStatusEffectProcessBase::VTMTick(float deltaTime)
{
	_elapsedTime += 10;

	if(_elapsedTime>_duration)
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
