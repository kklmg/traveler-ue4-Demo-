// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/BowAction/BowActionAim.h"
#include "Components/ActionComponent.h"
#include "Enums/EnumActionType.h"
#include "Enums/EnumAnimation.h"
#include "Components/AnimControlComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Character/CreatureCharacter.h"

UBowActionAim::UBowActionAim()
{
	_processName = NSNameWeaponActionProcess::AIM;
}


void UBowActionAim::VTMExecute()
{
	Super::VTMExecute();

	//Camera
	GetBow()->DragCamera(true);

	//Crosshair
	GetBow()->AnimateCrosshair(true);

	//Rotation
	GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, false);
}

void UBowActionAim::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	EAnimationState animationState = GetAnimControlComp()->GetAnimationState();
	if(animationState != EAnimationState::EAnimState_Walk && animationState != EAnimationState::EAnimState_Fall)
	{
		SetProcessAborted();
	}

	//let actor face to camera forward
	if (GetCameraInterface())
	{
		FQuat cameraQuat = GetCameraInterface()->VGetCameraRotation();
		FVector forward = cameraQuat.RotateVector(FVector::ForwardVector);
		forward.Z = 0;
		forward.Normalize();

		GetActionOwner()->SetActorRotation(forward.ToOrientationQuat());
	}
}

void UBowActionAim::VTMOnDead()
{
	Super::VTMOnDead();

	GetBow()->SetBowState(EBowState::EBS_Normal);

	//Camera
	GetBow()->DragCamera(false);

	//Crosshair
	GetBow()->AnimateCrosshair(false);

	//Movement
	GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, true);
}
