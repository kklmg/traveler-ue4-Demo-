// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeapon.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/WeaponBase.h"

UActionWeapon::UActionWeapon()
{
	_processName = NSNameWeaponActionProcess::FIRE;
	_actionType = EActionType::EACT_Aim;
	_bIsInstantProcess = false;
}

void UActionWeapon::VTMInit()
{
	Super::VTMInit();
	_weaponComp = Cast<UWeaponComponent>(GetActionOwner()->GetComponentByClass(UWeaponComponent::StaticClass()));
//	_weaponProcess = _weaponComp ? _weaponComp->GetWeaponProcess(_processName) : nullptr;
	if(_weaponProcess)
	{
		_weaponProcess->Init();
	}
}

bool UActionWeapon::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	if (_weaponComp == nullptr || _weaponProcess == nullptr) return false;
	return _weaponProcess->VCanExecute();
}

void UActionWeapon::VTMExecute()
{
	Super::VTMExecute();
	
	check(_weaponProcess);
	_weaponProcess->Execute();
}

void UActionWeapon::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	_weaponProcess->Tick(deltaTime);
}

void UActionWeapon::VTMOnDead()
{
	Super::VTMOnDead();

	check(GetWeaponComp());

	_weaponProcess->Abort();
}

UWeaponComponent* UActionWeapon::GetWeaponComp()
{
	return _weaponComp;
}
