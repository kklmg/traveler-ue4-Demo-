// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStopFire.h"
#include "Weapon/WeaponBase.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"

UActionWeaponStopFire::UActionWeaponStopFire()
{
	_processName = NSNameAction::WeaponFire;
	_actionType = EActionType::EACT_WeaponStopFire;
}

void UActionWeaponStopFire::VTMExecute()
{
	if (GetWeaponComp())
	{
		GetWeaponComp()->StopWeaponProcess(NSNameWeaponProcess::FIRE);
	}
}
