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
#include "GameSystem/travelerGameModeBase.h"
#include "GameSystem/PostProcessControlBase.h"
#include "Components/StatusComponent.h"
#include "Data/CostData.h"

UBowActionAim::UBowActionAim()
{
	_processName = NSNameWeaponActionProcess::AIM;
	_actionType = EActionType::EACT_Aim;
	_bIsInstantProcess = false;
	
	_slowMotionCost = CreateDefaultSubobject<UCostData>(TEXT("Cost"));
	_slowMotionCost->AddCost(EStatusType::EStatus_Mana, 0.25f);
	_slowMotion_timeDilation = 0.1f;
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

	_delegateHandle = GetBow()->OnBowStateChangedDelegate.AddUObject(this, &UBowActionAim::OnBowStateChanged);

	//Slow Motion
	if (GetActionOwner()->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling && GetStatusComp())
	{
		if (GetStatusComp()->GetRemainingValue(EStatusType::EStatus_Mana) > 20.0f && GetStatusComp()->TryApplyCost(_slowMotionCost))
		{
			ActivateSlowMotion(true);
		}
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

	//Slow Motion
	if (_bActiveSlowMotion)
	{
		if (GetStatusComp()->TryApplyCost(_slowMotionCost))
		{
			ActivateSlowMotion(true);
		}
		else
		{
			ActivateSlowMotion(false);
		}
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
	if (_bActiveSlowMotion == bActive) return;

	_bActiveSlowMotion = bActive;
	//Apply Time Dilation
	if (_bActiveSlowMotion)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), _slowMotion_timeDilation); //Global slow motions
		GetActionOwner()->CustomTimeDilation = 1.0f / _slowMotion_timeDilation;
		
		UMyCharacterMovementComponent* myMovementComp = Cast<UMyCharacterMovementComponent>(GetActionOwner()->GetCharacterMovement());
		if(myMovementComp)
		{
			myMovementComp->SetTimeDilation(_slowMotion_timeDilation);
		}

		auto gameMode = Cast<AtravelerGameModeBase>(GetWorld()->GetAuthGameMode());
		if(gameMode)
		{
			gameMode->GetPostProcessControl()->ActivateBlurEffect(true);
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

		auto gameMode = Cast<AtravelerGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gameMode)
		{
			gameMode->GetPostProcessControl()->ActivateBlurEffect(false);
		}
	}
}

