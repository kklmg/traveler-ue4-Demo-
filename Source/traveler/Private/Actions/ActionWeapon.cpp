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
	_weaponProcess = _weaponComp ? _weaponComp->GetWeaponProcess(_processName) : nullptr;
	if(_weaponProcess)
	{
		_weaponProcess->Init();
		_delegateHandle = _weaponProcess->ProcessStateChangedDelegate.AddUObject(this, &UActionWeapon::OnWeaponProcessStateChanged);
	}

	GetWeaponComp()->OnWeaponChanged.AddDynamic(this, &UActionWeapon::OnWeaponChanged);
}

bool UActionWeapon::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;
	if (_weaponComp == nullptr || _weaponProcess == nullptr) return false;
	return _weaponProcess->CanExecute();
}

void UActionWeapon::VTMExecute()
{
	Super::VTMExecute();
	
	check(_weaponProcess);

	_weaponProcess->Execute();
}

void UActionWeapon::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	_weaponProcess->Tick(deltaTime);
}

void UActionWeapon::VTMOnDead()
{
	Super::VTMOnDead();

	check(GetWeaponComp());

	_weaponProcess->Abort();
	_weaponProcess->ProcessStateChangedDelegate.Remove(_delegateHandle);
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

void UActionWeapon::OnWeaponProcessStateChanged(EProcessState processState)
{
	check(_weaponProcess);

	if(_weaponProcess->IsDead())
	{
		SetProcessAborted();
	}
}
