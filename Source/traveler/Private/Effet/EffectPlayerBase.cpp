// Fill out your copyright notice in the Description page of Project Settings.


#include "Effet/EffectPlayerBase.h"
#include "Containers/Set.h"

FActorEffectData::FActorEffectData()
{
	BlendColor = FLinearColor::White;
}

FActorEffectData::FActorEffectData(FLinearColor color)
{
	BlendColor = color;
}

UEffectPlayerBase::UEffectPlayerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_alpha = 0.2f;

	_matColorParams.Association = EMaterialParameterAssociation::LayerParameter;
	_matColorParams.Name = FName("Color");
	_matColorParams.Index = 1;

	_effectData.Empty();
	_effectData.Add(EStatusEffect::EStatusEffect_Fire, FLinearColor::Red);
	_effectData.Add(EStatusEffect::EStatusEffect_Ice, FLinearColor(0, 1, 1, 1));
	_effectData.Add(EStatusEffect::EStatusEffect_Electricity, FLinearColor::Yellow);
	_effectData.Add(EStatusEffect::EStatusEffect_Poison, FLinearColor(0.5, 0, 0.5, 1));
	_effectData.Add(EStatusEffect::EStatusEffect_Water, FLinearColor::Blue);
}

void UEffectPlayerBase::Initialize(AActor* owner, UMaterialInstanceDynamic* mid)
{
	_owner = owner;
	_mid = mid;
}

void UEffectPlayerBase::PlayEffect(EStatusEffect effectType)
{
	if (_runningEffect.Contains(effectType)) return;
	if (!_effectData.Contains(effectType)) return;

	_runningEffect.Add(effectType);

	//color setting
	ApplyBlendedColor();

	//Destroy Effect Actor
	if(_effectData[effectType].EffectActorIns)
	{
		_effectData[effectType].EffectActorIns->Destroy();
		_effectData[effectType].EffectActorIns = nullptr;
	}

	//Spawn Effect Actor
	if (_effectData[effectType].EffectActorClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = _owner;

		_effectData[effectType].EffectActorIns = GetWorld()->SpawnActor<AActor>(_effectData[effectType].EffectActorClass, spawnParams);
		_effectData[effectType].EffectActorIns->AttachToActor(_owner, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void UEffectPlayerBase::StopEffect(EStatusEffect effectType)
{
	if (!_runningEffect.Contains(effectType)) return;
	if (!_effectData.Contains(effectType)) return;

	_runningEffect.Remove(effectType);

	//Color setting
	ApplyBlendedColor();

	//Destroy Effect Actor
	if (_effectData[effectType].EffectActorIns)
	{
		_effectData[effectType].EffectActorIns->Destroy();
		_effectData[effectType].EffectActorIns = nullptr;
	}
}

UMaterialInstanceDynamic* UEffectPlayerBase::GetMaterial()
{
	return _mid;
}

void UEffectPlayerBase::ApplyBlendedColor()
{
	if (_runningEffect.Num() == 0)
	{
		_blendedColor.A = 0;
	}
	else
	{
		auto iter = _runningEffect.begin();

		if (iter && _effectData.Contains(*iter))
		{
			_blendedColor = _effectData[*iter].BlendColor;
			++iter;
		}

		for (; iter; ++iter)
		{
			if (_effectData.Contains(*iter))
			{
				_blendedColor = FMath::LerpStable(_blendedColor, _effectData[*iter].BlendColor, 0.5f);
			}
		}
		_blendedColor.A = _alpha;
	}

	if (_mid)
	{
		_mid->SetVectorParameterValueByInfo(_matColorParams, _blendedColor);
	}
}
