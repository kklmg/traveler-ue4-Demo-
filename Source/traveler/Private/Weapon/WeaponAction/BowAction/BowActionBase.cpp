// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/BowAction/BowActionBase.h"



void UBowActionBase::VSetWeapon(AWeaponBase* weapon)
{
	Super::VSetWeapon(weapon);

	if(weapon->GetWeaponType() == EWeaponType::EWT_Bow)
	{
		_bow = Cast<ABowBase>(weapon);
		check(_bow);
	}
}

FORCEINLINE_DEBUGGABLE ABowBase* UBowActionBase::GetBow()
{
	return _bow;
}
