// Fill out your copyright notice in the Description page of Project Settings.


#include "Effet/EffectPlayer_StatusEffect.h"
#include "Containers/Set.h"


FEffectData_StatusEffect::FEffectData_StatusEffect() : BlendColor(FLinearColor::White)
{
}

FEffectData_StatusEffect::FEffectData_StatusEffect(FLinearColor& color) : BlendColor(color)
{
}

UEffectPlayer_StatusEffect::UEffectPlayer_StatusEffect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_alpha = 0.2f;

	_matParamInfo_Color.Association = EMaterialParameterAssociation::LayerParameter;
	_matParamInfo_Color.Name = FName("Color");
	_matParamInfo_Color.Index = 1;

	
	//_effectData.Add(EStatusEffect::EStatusEffect_Fire, FLinearColor::Red));
	//_effectData.Add(EStatusEffect::EStatusEffect_Fire, FEffectData_StatusEffect(FLinearColor::Red));
	//_effectData.Add(EStatusEffect::EStatusEffect_Ice, FEffectData_StatusEffect(FLinearColor(0, 1, 1, 1)));
	//_effectData.Add(EStatusEffect::EStatusEffect_Electricity, FEffectData_StatusEffect(FLinearColor::Yellow));
	//_effectData.Add(EStatusEffect::EStatusEffect_Poison, FEffectData_StatusEffect(FLinearColor(0.5, 0, 0.5, 1)));
	//_effectData.Add(EStatusEffect::EStatusEffect_Water, FEffectData_StatusEffect(FLinearColor::Blue));
}

void UEffectPlayer_StatusEffect::VPlayEffect(uint8 effectOption)
{
	EStatusEffect statusEffectType = (EStatusEffect)effectOption;
	if (_runningEffect.Contains(statusEffectType)) return;
	if (!_effectData.Contains(statusEffectType)) return;

	_runningEffect.Add(statusEffectType);

	//color setting
	BlendColors();

	//Destroy Effect Actor
	if (_effectData[statusEffectType].EffectActorIns)
	{
		_effectData[statusEffectType].EffectActorIns->Destroy();
		_effectData[statusEffectType].EffectActorIns = nullptr;
	}

	//Spawn Effect Actor
	if (_effectData[statusEffectType].EffectActorClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = GetOwner();

		_effectData[statusEffectType].EffectActorIns = GetWorld()->SpawnActor<AActor>(_effectData[statusEffectType].EffectActorClass, spawnParams);
		_effectData[statusEffectType].EffectActorIns->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	}
}

void UEffectPlayer_StatusEffect::VStopEffect(uint8 effectOption)
{
	EStatusEffect statusEffectType = (EStatusEffect)effectOption;

	if (!_runningEffect.Contains(statusEffectType)) return;
	if (!_effectData.Contains(statusEffectType)) return;

	_runningEffect.Remove(statusEffectType);

	//Blend Color
	BlendColors();

	//Destroy Effect Actor
	if (_effectData[statusEffectType].EffectActorIns)
	{
		_effectData[statusEffectType].EffectActorIns->Destroy();
		_effectData[statusEffectType].EffectActorIns = nullptr;
	}
}

void UEffectPlayer_StatusEffect::VTick(float deltaTime)
{
}

void UEffectPlayer_StatusEffect::BlendColors()
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

	if (GetMaterial())
	{
		GetMaterial()->SetVectorParameterValueByInfo(_matParamInfo_Color, _blendedColor);
	}
}