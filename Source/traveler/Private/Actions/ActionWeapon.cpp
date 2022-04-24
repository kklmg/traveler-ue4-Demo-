// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeapon.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/WeaponBase.h"

UActionWeapon::UActionWeapon()
{
	_processName = NSNameWeaponProcess::FIRE;
	_actionType = EActionType::EACT_Aim;
	_bIsInstantProcess = false;
}

void UActionWeapon::VTMInit()
{
	Super::VTMInit();
	_weaponComp = Cast<UWeaponComponent>(GetActionOwner()->GetComponentByClass(UWeaponComponent::StaticClass()));
}

bool UActionWeapon::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;

	return _weaponComp != nullptr;
}

void UActionWeapon::VTMExecute()
{
	Super::VTMExecute();

	check(_weaponComp);

	GetWeaponComp()->ExecuteWeaponProcess(_processName);
	GetWeaponComp()->OnWeaponChanged.AddDynamic(this, &UActionWeapon::OnWeaponChanged);
}

void UActionWeapon::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	GetWeaponComp()->ExecuteWeaponProcess(_processName);
}

void UActionWeapon::VTMOnDead()
{
	Super::VTMOnDead();

	check(GetWeaponComp());

	GetWeaponComp()->StopWeaponProcess(_processName);
	GetWeaponComp()->OnWeaponChanged.RemoveDynamic(this, &UActionWeapon::OnWeaponChanged);
}

UWeaponComponent* UActionWeapon::GetWeaponComp()
{
	return _weaponComp;
}

void UActionWeapon::OnWeaponChanged(AWeaponBase* weaponIns)
{
	SetProcessAborted();
}