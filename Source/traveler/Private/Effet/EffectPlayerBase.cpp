// Fill out your copyright notice in the Description page of Project Settings.


#include "Effet/EffectPlayerBase.h"

FActorEffectData::FActorEffectData()
{
	BlendColor = FLinearColor::White;
}

FActorEffectData::FActorEffectData(FLinearColor color)
{
	BlendColor = FLinearColor(0, 0, 0, 0);
}

UEffectPlayerBase::UEffectPlayerBase()
{
	_blendColor = FLinearColor::White;

	_matColorParams.Association = EMaterialParameterAssociation::LayerParameter;
	_matColorParams.Name = FName("Color");
	_matColorParams.Index = 1;

	_effectData.Add(EStatusEffect::EStatusEffect_Fire, FLinearColor::Red);
	_effectData.Add(EStatusEffect::EStatusEffect_Ice, FLinearColor(0, 1, 1, 1));
	_effectData.Add(EStatusEffect::EStatusEffect_Electricity, FLinearColor::Yellow);
	_effectData.Add(EStatusEffect::EStatusEffect_Poison, FLinearColor(0.5, 0, 0.5, 1));
	_effectData.Add(EStatusEffect::EStatusEffect_Water, FLinearColor::Blue);
}

void UEffectPlayerBase::Initialize(UMaterialInstanceDynamic* mid)
{
	_mid = mid;
}

void UEffectPlayerBase::PlayEffect(EStatusEffect effectType)
{
	if (_runningEffect.Contains(effectType)) return;
	if (!_effectData.Contains(effectType)) return;

	_runningEffect.Add(effectType);

	//Color setting
	_blendColor = _blendColor * _effectData[effectType].BlendColor;
	if (_mid)
	{
		//_mid->SetVectorParameterValueByInfo(_matColorParams, _blendColor);

		FMaterialParameterInfo matTest;
		matTest.Association = EMaterialParameterAssociation::BlendParameter;
		matTest.Name = FName("Alpha");
		matTest.Index = 1;

		_mid->SetScalarParameterValueByInfo(matTest, 0.5);
	}

}

void UEffectPlayerBase::StopEffect(EStatusEffect effectType)
{
	if (!_runningEffect.Contains(effectType)) return;
	if (!_effectData.Contains(effectType)) return;

	_runningEffect.Remove(effectType);

	//Color setting
	_blendColor = _blendColor / _effectData[effectType].BlendColor;
	if (_mid)
	{
		_mid->SetVectorParameterValueByInfo(_matColorParams, _blendColor);
	}
}

UMaterialInstanceDynamic* UEffectPlayerBase::GetMaterial()
{
	return _mid;
}