// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/BowAction/BowActionAim.h"
#include "Components/ActionComponent.h"
#include "Enums/EnumActionType.h"
#include "Enums/EnumAnimation.h"
#include "Components/AnimControlComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Character/CreatureCharacter.h"
#include "Data/WeaponAnimationModelBase.h"

UBowActionAim::UBowActionAim()
{
	_processName = NSNameWeaponActionProcess::AIM;
	_actionType = EActionType::EACT_Aim;
	_bIsInstantProcess = false;
}


void UBowActionAim::VOnExecute()
{
	Super::VOnExecute();

	//Camera
	GetBow()->DragCamera(true);

	//Crosshair
	GetBow()->AnimateCrosshair(true);

	//Rotation
	GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, false);

	//Animation
	GetBow()->GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsAiming, true);
}



void UBowActionAim::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

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

void UBowActionAim::VOnDead()
{
	Super::VOnDead();

	GetBow()->SetBowState(EBowState::EBS_Normal);

	//Camera
	GetBow()->DragCamera(false);

	//Crosshair
	GetBow()->AnimateCrosshair(false);

	//Movement
	GetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, true);

	//Animation
	GetBow()->GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsAiming, false);
}
