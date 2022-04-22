// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStartAim.h"
#include "Weapon/WeaponBase.h"
#include "Components/WeaponComponent.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"

UActionWeaponStartAim::UActionWeaponStartAim()
{
	_processName = NSNameAction::WeaponAim;
	_actionType = EActionType::EACT_WeaponStartAim;
	_bIsInstantProcess = true;
}

void UActionWeaponStartAim::VTMExecute()
{ 
	if(GetWeaponComp())
	{
		GetWeaponComp()->ExecuteWeaponProcess(NSNameWeaponProcess::AIM);
	}
}
