// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/BowAction/BowActionFire.h"
#include "Components/AnimControlComponent.h"
#include "Data/WeaponAnimationModelBase.h"
#include "Enums/EnumAnimation.h"

UBowActionFire::UBowActionFire()
{
	_processName = NSNameWeaponActionProcess::FIRE;
	_actionType = EActionType::EACT_Fire;
}

bool UBowActionFire::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	return GetBow()->VCanFire();
}

void UBowActionFire::VTMExecute()
{
	Super::VTMExecute();

	EAnimationState animationState = GetAnimControlComp()->GetAnimationState();
	if (animationState != EAnimationState::EAnimState_Walk && animationState != EAnimationState::EAnimState_Fall)
	{
		SetProcessAborted();
	}

	GetBow()->SetBowState(EBowState::EBS_ReleaseStart);

	//Animation
	GetBow()->GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsFiring, true);
}

void UBowActionFire::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}

void UBowActionFire::VTMOnDead()
{
	Super::VTMOnDead();

	//Animation
	GetBow()->GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsFiring, false);
}