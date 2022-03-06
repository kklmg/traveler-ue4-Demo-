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
	_weapon = weapon;

	if (_weapon == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("set weapon failed"));
	}
}

float UWeaponProcessBase::GetElapsedTime()
{
	return _elapsedTime;
}
