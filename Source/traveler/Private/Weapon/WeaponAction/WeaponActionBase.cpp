// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/WeaponActionBase.h"
#include "GameFramework/Character.h"
#include "Components/WeaponComponent.h"

void UWeaponActionBase::VSetUpActionData(ACharacter* character, UActionComponent* actionComp)
{
	Super::VSetUpActionData(character, actionComp);
	_weaponComp = Cast<UWeaponComponent>(character->GetComponentByClass(UWeaponComponent::StaticClass()));
}

bool UWeaponActionBase::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	return _weaponComp != nullptr && _weaponComp->GetEquipedWeapon() != nullptr;
}

UWeaponComponent* UWeaponActionBase::GetWeaponComp()
{
	return _weaponComp;
}