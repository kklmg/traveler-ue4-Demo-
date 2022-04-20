// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStopAim.h"
#include "Weapon/WeaponBase.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"

UActionWeaponStopAim::UActionWeaponStopAim()
{
	_actionName = ActionName::WeaponAim;
	_actionType = EActionType::EACT_WeaponStopAim;
}

void UActionWeaponStopAim::VTMExecute()
{
	if (GetWeaponComp())
	{
		GetWeaponComp()->StopWeaponProcess(NSNameWeaponProcess::AIM);
	}
}
