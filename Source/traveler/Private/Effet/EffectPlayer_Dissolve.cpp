// Fill out your copyright notice in the Description page of Project Settings.


#include "Effet/EffectPlayer_Dissolve.h"

UEffectPlayer_Dissolve::UEffectPlayer_Dissolve(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_matParamInfo_DissolveAmount.Association = EMaterialParameterAssociation::LayerParameter;
	_matParamInfo_DissolveAmount.Name = FName("Dissolve Amount");
	_matParamInfo_DissolveAmount.Index = 2;

	_dissolveAmount = 0;
	_duration = 5;
}

void UEffectPlayer_Dissolve::VPlayEffect(uint8 effectOption)
{
	_bForward = true;
}


void UEffectPlayer_Dissolve::VStopEffect(uint8 effectOption)
{
	_bForward = false;
}

void UEffectPlayer_Dissolve::VTick(float deltaTime)
{
	if (!GetMaterial()) return;
	if (!_dissolveAmountCurve) return;
	if (_bForward && _elapsedTime == _duration) return;
	if ((!_bForward) && _elapsedTime == 0.0f) return;
	
	//compute Normalized elapsed Time
	_elapsedTime = _bForward ? _elapsedTime + deltaTime : _elapsedTime - deltaTime;
	_elapsedTime = FMath::Clamp(_elapsedTime, 0.0f, _duration);
	float normalizedElapsedTime = _elapsedTime / _duration;

	//Set Material Parameter value
	_dissolveAmount = _dissolveAmountCurve->GetFloatValue(normalizedElapsedTime);
	GetMaterial()->SetScalarParameterValueByInfo(_matParamInfo_DissolveAmount, _dissolveAmount);
}
