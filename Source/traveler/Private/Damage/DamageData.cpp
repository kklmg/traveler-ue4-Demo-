// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/DamageData.h"
#include "Data/StatusEffectData.h"

FDamageData::FDamageData()
{
	ElementalType = EElementalType::EElemental_Physics; 
	Damage = 0.f;
}