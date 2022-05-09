// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/WeaponActionBase.h"
#include "Weapon/WeaponBase.h"

void UWeaponActionBase::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}

void UWeaponActionBase::VTMOnDead()
{
	Super::VTMOnDead();
}


void UWeaponActionBase::VSetWeapon(AWeaponBase* weapon)
{
	check(weapon);
	_weapon = weapon;
}