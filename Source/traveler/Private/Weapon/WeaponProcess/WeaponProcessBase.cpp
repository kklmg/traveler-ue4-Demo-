// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProcess/WeaponProcessBase.h"
#include "Weapon/WeaponBase.h"

void UWeaponProcessBase::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	_elapsedTime += deltaTime;
}

void UWeaponProcessBase::VTMOnDead()
{
	Super::VTMOnDead();

	_elapsedTime = 0;
}


void UWeaponProcessBase::VSetWeapon(AWeaponBase* weapon)
{
	check(weapon);

	_weapon = weapon;
}

float UWeaponProcessBase::GetElapsedTime()
{
	return _elapsedTime;
}
