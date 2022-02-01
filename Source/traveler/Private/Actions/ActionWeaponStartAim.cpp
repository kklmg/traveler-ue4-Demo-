// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStartAim.h"
#include "Interface/WeaponInterface.h"
#include "GameFramework/Character.h"

UActionWeaponStartAim::UActionWeaponStartAim()
{
	_actionName = ActionName::WeaponAim;
	_actionType = EActionType::EACT_WeaponStartAim;
}

void UActionWeaponStartAim::VTMExecute()
{
	IWeaponInterface* weaponInterface = Cast<IWeaponInterface>(GetActionOwner());
	if(weaponInterface)
	{
		weaponInterface->VStartAiming();
	}
}
