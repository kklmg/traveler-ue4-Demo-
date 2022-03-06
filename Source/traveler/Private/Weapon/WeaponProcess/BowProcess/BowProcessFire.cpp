// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProcess/BowProcess/BowProcessFire.h"


FName UBowProcessFire::VGetProcessName()
{
	return WeaponProcessName::FIRE;
}

bool UBowProcessFire::VTMCanExecute()
{
	if (!_bow) return false;
	
	EAnimationState animationState = _bow->GetOwnerAnimationState();
	
	return (animationState == EAnimationState::EAnimState_Walk || animationState == EAnimationState::EAnimState_Fall);
}

void UBowProcessFire::VTMExecute()
{
	Super::VTMExecute();
	if (!_bow) return;
	EBowState bowState = _bow->GetBowState();

	if(_bow->IsProcessRunning(WeaponProcessName::AIM) && 
		(bowState == EBowState::EBS_FullyDrawed || bowState == EBowState::EBS_OverDrawing))
	{
		_bow->SetBowState(EBowState::EBS_ReleaseStart);
	}
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