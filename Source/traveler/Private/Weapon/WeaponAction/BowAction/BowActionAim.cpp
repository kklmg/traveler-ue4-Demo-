// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/BowAction/BowActionAim.h"
#include "Components/ActionComponent.h"
#include "Enums/EnumActionType.h"
#include "Enums/EnumAnimation.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Character/CreatureCharacter.h"

UBowActionAim::UBowActionAim()
{
	_processName = NSNameWeaponActionProcess::AIM;
}

bool UBowActionAim::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	if (!GetBow()) return false;

	EAnimationState animationState = GetBow()->GetOwnerAnimationState();

	return (animationState == EAnimationState::EAnimState_Walk || animationState == EAnimationState::EAnimState_Fall)
		&& (GetBow()->GetOwnerActionComp()->IsActionRunning(EActionType::EACT_Dodge) == false);
}

void UBowActionAim::VTMExecute()
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

void UBowActionAim::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
	if (!GetBow()) return;


	ICharacterCameraInterface* cameraInterface = GetBow()->GetOwnerCameraInterface();
	ACreatureCharacter* weaponOwner = GetBow()->GetWeaponOwner();
	//make actor face to camera forward
	if (weaponOwner && cameraInterface)
	{
		FQuat cameraQuat = cameraInterface->VGetCameraRotation();
		FVector forward = cameraQuat.RotateVector(FVector::ForwardVector);
		forward.Z = 0;
		forward.Normalize();

		weaponOwner->SetActorRotation(forward.ToOrientationQuat());
	}
}

void UBowActionAim::VTMOnDead()
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
