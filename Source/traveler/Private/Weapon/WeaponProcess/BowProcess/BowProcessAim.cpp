// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProcess/BowProcess/BowProcessAim.h"
#include "Components/ActionComponent.h"
#include "Enums/EnumActionType.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Character/CreatureCharacter.h"

FName UBowProcessAim::VGetProcessName()
{
	return NSNameWeaponProcess::AIM;
}

bool UBowProcessAim::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;
	if (!GetBow()) return false;

	EAnimationState animationState = GetBow()->GetOwnerAnimationState();

	return (animationState == EAnimationState::EAnimState_Walk || animationState == EAnimationState::EAnimState_Fall)
		&& (GetBow()->GetOwnerActionComp()->CheckActionIsInProgress(EActionType::EACT_Dodge) == false);
}

void UBowProcessAim::VTMExecute()
{
	Super::VTMExecute();

	check(GetBow());

	//Camera
	GetBow()->DragCamera(true);

	//Crosshair
	GetBow()->AnimateCrosshair(true);

	//Movement
	if (GetBow()->GetOwnerActionComp())
	{
		GetBow()->GetOwnerActionComp()->GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, false);
	}
}

void UBowProcessAim::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
	if (!GetBow()) return;


	ICharacterCameraInterface* cameraInterface = GetBow()->GetOwnerCameraInterface();
	ACreatureCharacter* weaponOwner = GetBow()->GetWeaponOwner();
	//make actor face to camera forward
	if (weaponOwner && cameraInterface)
	{
		FRotator cameraRotator = cameraInterface->VGetCameraRotation();
		cameraRotator.Pitch = 0;
		cameraRotator.Roll = 0;

		weaponOwner->SetActorRotation(cameraRotator);
	}
}

void UBowProcessAim::VTMReset()
{
	Super::VTMReset();
}

void UBowProcessAim::VTMOnDead()
{
	Super::VTMOnDead();
	if (!GetBow()) return;

	GetBow()->SetBowState(EBowState::EBS_Normal);

	//Camera
	GetBow()->DragCamera(false);

	//Crosshair
	GetBow()->AnimateCrosshair(false);

	//Movement
	if (GetBow()->GetOwnerActionComp())
	{
		GetBow()->GetOwnerActionComp()->GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, true);
	}
}
