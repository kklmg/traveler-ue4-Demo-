// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/StatusEffectData.h"

// Sets default values
UStatusEffectData::UStatusEffectData()
{
	StatusEffectType = EStatusEffect::EStatusEffect_NONE;
	Damage = 10;
	DamageInterval = 1.0f;
	EffectDuration = 15.0f;
}


