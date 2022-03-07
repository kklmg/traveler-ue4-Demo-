// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProcess/BowProcess/BowProcessFire.h"


FName UBowProcessFire::VGetProcessName()
{
	return WeaponProcessName::FIRE;
}

bool UBowProcessFire::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;
	if (!_bow) return false;
	
	EAnimationState animationState = _bow->GetOwnerAnimationState();
	EBowState bowState = _bow->GetBowState();
	
	bool bCharacterCanFire = animationState == EAnimationState::EAnimState_Walk || animationState == EAnimationState::EAnimState_Fall;
	bool bIsAimingMode = _bow->IsProcessRunning(WeaponProcessName::AIM);
	bool bBowCanFire = bowState == EBowState::EBS_FullyDrawed || bowState == EBowState::EBS_OverDrawing;

	//todo: firing in normal mode
	return bIsAimingMode ? bCharacterCanFire && bBowCanFire : false;
}

void UBowProcessFire::VTMExecute()
{
	Super::VTMExecute();
	if (!_bow) return;

	bool bIsAimingMode = _bow->IsProcessRunning(WeaponProcessName::AIM);

	if(bIsAimingMode)
	{
		_bow->SetBowState(EBowState::EBS_ReleaseStart);
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

void UBowProcessFire::VTMReset()
{
	Super::VTMReset();
}

void UBowProcessFire::VTMOnDead()
{
	Super::VTMOnDead();
}