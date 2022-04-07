// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProcess/BowProcess/BowProcessAim.h"
#include "Interface/ActionInterface.h"
#include "Character/CreatureCharacter.h"

FName UBowProcessAim::VGetProcessName() 
{
	return WeaponProcessName::AIM;
}

bool UBowProcessAim::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;
	if (!_bow) return false;
	
	IActionInterface* actionInterface = _bow->GetOwnerActionInterface();
	if (!actionInterface) return false;

	EAnimationState animationState = _bow->GetOwnerAnimationState();


	return (animationState == EAnimationState::EAnimState_Walk || animationState == EAnimationState::EAnimState_Fall)
		&& (actionInterface->VCheckActionIsInProgress(EActionType::EACT_Dodge) == false);
}

void UBowProcessAim::VTMExecute()
{
	Super::VTMExecute();
	if (!_bow) return;

	//Camera
	_bow->DragCamera(true);

	//Crosshair
	_bow->AnimateCrosshair(true);

	//Movement
	IActionInterface* actionInterface = _bow->GetOwnerActionInterface();
	if(actionInterface)
	{
		actionInterface->VGetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, false);
	}	
}

void UBowProcessAim::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
	if (!_bow) return;


	ICharacterCameraInterface* cameraInterface = _bow->GetOwnerCameraInterface();
	ACreatureCharacter* weaponOwner = _bow->GetWeaponOwner();
	//make actor face to camera forward
	if(weaponOwner && cameraInterface)
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
	if (!_bow) return;

	_bow->SetBowState(EBowState::EBS_Normal);

	//Camera
	_bow->DragCamera(false);

	//Crosshair
	_bow->AnimateCrosshair(false);

	//Movement
	IActionInterface* actionInterface = _bow->GetOwnerActionInterface();
	if (actionInterface)
	{
		actionInterface->VGetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, true);
	}
}
