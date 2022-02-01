// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStopAim.h"
#include "Interface/WeaponInterface.h"
#include "GameFramework/Character.h"

UActionWeaponStopAim::UActionWeaponStopAim()
{
	_actionName = ActionName::WeaponAim;
	_actionType = EActionType::EACT_WeaponStopAim;
}

void UActionWeaponStopAim::VTMExecute()
{
	IWeaponInterface* weaponInterface = Cast<IWeaponInterface>(GetActionOwner());
	if (weaponInterface)
	{
		weaponInterface->VStopAiming();
	}
}
