// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStartFire.h"
#include "Weapon/WeaponBase.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"

UActionWeaponStartFire::UActionWeaponStartFire()
{
	_actionName = ActionName::WeaponFire;
	_actionType = EActionType::EACT_WeaponStartFire;
}

void UActionWeaponStartFire::VTMExecute()
{
	if (GetWeaponComp())
	{
		GetWeaponComp()->ExecuteWeaponProcess(NSNameWeaponProcess::FIRE);
	}
}
