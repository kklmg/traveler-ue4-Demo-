// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProcess/BowProcess/BowProcessBase.h"



void UBowProcessBase::VSetWeapon(AWeaponBase* weapon)
{
	Super::VSetWeapon(weapon);

	if(weapon->GetWeaponType() == EWeaponType::EWT_Bow)
	{
		_bow = Cast<ABowBase>(weapon);
	}

	if (_bow == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Initialize bow process failed"));
	}
}
