// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStartFire.h"
#include "Interface/WeaponInterface.h"
#include "GameFramework/Character.h"

UActionWeaponStartFire::UActionWeaponStartFire()
{
	_actionName = ActionName::WeaponFire;
	_actionType = EActionType::EACT_WeaponStartFire;
}

void UActionWeaponStartFire::VTMExecute()
{
	IWeaponInterface* weaponInterface = Cast<IWeaponInterface>(GetActionOwner());
	if (weaponInterface)
	{
		weaponInterface->VExecuteWeaponProcess(WeaponProcessName::FIRE);
	}
}
