// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/BowAction/BowActionAim.h"
#include "Components/ActionComponent.h"
#include "Enums/EnumActionType.h"
#include "Enums/EnumAnimation.h"
#include "Components/AnimControlComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Character/CreatureCharacter.h"
#include "Data/WeaponAnimationModelBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MyCharacterMovementComponent.h"

UBowActionAim::UBowActionAim()
{
	_processName = NSNameWeaponActionProcess::AIM;
	_actionType = EActionType::EACT_Aim;
	_bIsInstantProcess = false;
	_timeDilation = 0.1f;
}


void UBowActionAim::VOnExecute()
{
	Super::VOnExecute();

	//Camera
	GetBow()->DragCamera(true);

	//Crosshair
	GetBow()->AnimateCrosshair(true);

	//Rotation
	GetActionBlackBoard()->WriteData_Bool(NSActionData::FaceToDest::Name, false);

	//Animation
	GetBow()->GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsAiming, true);

	//Slow Motion
	if (GetActionOwner()->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
	{
		ActivateSlowMotion(true);
	}
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

	_delegateHandle = GetBow()->OnBowStateChangedDelegate.AddUObject(this, &UBowActionAim::OnBowStateChanged);
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
	GetActionBlackBoard()->WriteData_Bool(NSActionData::FaceToDest::Name, true);

	//Animation
	GetBow()->GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsAiming, false);

	GetBow()->OnBowStateChangedDelegate.Remove(_delegateHandle);

	//Slow Motion
	ActivateSlowMotion(false);
}

void UBowActionAim::OnBowStateChanged(EBowState bowState)
{




}

void UBowActionAim::ActivateSlowMotion(bool bActive)
{
	//Apply Time Dilation
	if (bActive)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), _timeDilation); //Global slow motions
		GetActionOwner()->CustomTimeDilation = 1.0f / _timeDilation;
		
		UMyCharacterMovementComponent* myMovementComp = Cast<UMyCharacterMovementComponent>(GetActionOwner()->GetCharacterMovement());
		if(myMovementComp)
		{
			myMovementComp->SetTimeDilation(_timeDilation);
		}
	}
	//Recover Time Dilation
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f); //Global slow motions
		
		GetActionOwner()->CustomTimeDilation = 1.0f;

		UMyCharacterMovementComponent* myMovementComp = Cast<UMyCharacterMovementComponent>(GetActionOwner()->GetCharacterMovement());
		if (myMovementComp)
		{
			myMovementComp->SetTimeDilation(1.0f);
		}
	}
}

