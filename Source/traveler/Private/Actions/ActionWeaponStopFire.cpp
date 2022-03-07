// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStopFire.h"
#include "Interface/WeaponInterface.h"
#include "GameFramework/Character.h"

UActionWeaponStopFire::UActionWeaponStopFire()
{
	_actionName = ActionName::WeaponFire;
	_actionType = EActionType::EACT_WeaponStopFire;
}

void UActionWeaponStopFire::VTMExecute()
{
	IWeaponInterface* weaponInterface = Cast<IWeaponInterface>(GetActionOwner());
	if (weaponInterface)
	{
		weaponInterface->VStopWeaponProcess(WeaponProcessName::FIRE);
	}
}
