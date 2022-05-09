// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/BowAction/BowActionFire.h"
#include "Enums/EnumAnimation.h"

UBowActionFire::UBowActionFire()
{
	_processName = NSNameWeaponActionProcess::FIRE;
}

bool UBowActionFire::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	if (!GetBow()) return false;
	
	EAnimationState animationState = GetBow()->GetOwnerAnimationState();
	EBowState bowState = GetBow()->GetBowState();
	
	bool bCharacterCanFire = animationState == EAnimationState::EAnimState_Walk || animationState == EAnimationState::EAnimState_Fall;
	bool bIsAimingMode = GetBow()->IsProcessRunning(NSNameWeaponActionProcess::AIM);
	bool bBowCanFire = bowState == EBowState::EBS_FullyDrawed || bowState == EBowState::EBS_OverDrawing;

	//todo: firing in normal mode
	return bIsAimingMode ? bCharacterCanFire && bBowCanFire : false;
}

void UBowActionFire::VTMExecute()
{
	Super::VTMExecute();
	if (!GetBow()) return;

	bool bIsAimingMode = GetBow()->IsProcessRunning(NSNameWeaponActionProcess::AIM);

	if(bIsAimingMode)
	{
		GetBow()->SetBowState(EBowState::EBS_ReleaseStart);
	}
	//todo: firing in normal mode
	else
	{
		
	}
}

void UBowActionFire::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}

void UBowActionFire::VTMOnDead()
{
	Super::VTMOnDead();
}