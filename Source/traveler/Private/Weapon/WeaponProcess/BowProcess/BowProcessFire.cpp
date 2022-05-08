// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProcess/BowProcess/BowProcessFire.h"
#include "Enums/EnumAnimation.h"

UBowProcessFire::UBowProcessFire()
{
	_processName = NSNameWeaponProcess::FIRE;
}

bool UBowProcessFire::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	if (!GetBow()) return false;
	
	EAnimationState animationState = GetBow()->GetOwnerAnimationState();
	EBowState bowState = GetBow()->GetBowState();
	
	bool bCharacterCanFire = animationState == EAnimationState::EAnimState_Walk || animationState == EAnimationState::EAnimState_Fall;
	bool bIsAimingMode = GetBow()->IsProcessRunning(NSNameWeaponProcess::AIM);
	bool bBowCanFire = bowState == EBowState::EBS_FullyDrawed || bowState == EBowState::EBS_OverDrawing;

	//todo: firing in normal mode
	return bIsAimingMode ? bCharacterCanFire && bBowCanFire : false;
}

void UBowProcessFire::VTMExecute()
{
	Super::VTMExecute();
	if (!GetBow()) return;

	bool bIsAimingMode = GetBow()->IsProcessRunning(NSNameWeaponProcess::AIM);

	if(bIsAimingMode)
	{
		GetBow()->SetBowState(EBowState::EBS_ReleaseStart);
	}
	//todo: firing in normal mode
	else
	{
		
	}
}

void UBowProcessFire::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}

void UBowProcessFire::VTMOnDead()
{
	Super::VTMOnDead();
}