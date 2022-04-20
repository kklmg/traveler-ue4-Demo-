// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWeaponStartAim.h"
#include "Weapon/WeaponBase.h"
#include "Components/WeaponComponent.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"

UActionWeaponStartAim::UActionWeaponStartAim()
{
	_actionName = ActionName::WeaponAim;
	_actionType = EActionType::EACT_WeaponStartAim;
	_bInstantAction = true;
}

void UActionWeaponStartAim::VInitialize(ACharacter* character, UActionComponent* actionComp, UActionBlackBoard* actionBlackBoard)
{
	Super::VInitialize(character, actionComp, actionBlackBoard);
}

void UActionWeaponStartAim::VTMExecute()
{
	if(GetWeaponComp())
	{
		GetWeaponComp()->ExecuteWeaponProcess(NSNameWeaponProcess::AIM);
	}
}
