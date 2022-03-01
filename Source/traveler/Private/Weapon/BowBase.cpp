// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BowBase.h"
#include "Actors/ArrowActorBase.h"
#include "Character/CreatureCharacter.h"
#include "Components/PawnCameraComponent.h"
#include "Components/QuiverComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Command/CommandActor.h"
#include "Interface/CharacterCameraInterface.h"
#include "Interface/MeshSocketTransformProvider.h"
#include "Interface/ActionInterface.h"
#include "UI/CrosshairWidgetBase.h"


ABowBase::ABowBase()
{
	//Create quiver component used in projectile management
	if (_quiverComponent == nullptr)
	{
		_quiverComponent = CreateDefaultSubobject<UQuiverComponent>(TEXT("QuiverComponent"));
		check(_quiverComponent != nullptr);
	}

	WeaponType = EWeaponType::EWT_Bow;
	_bowState = EBowState::EBS_Normal;

	_strength = 0.0f;
	_maxDamage = 0.0f;
	_drawingVelocity = 0.5f;
	_baseProjectileVelocity = 1000.0f;
	_maxProjectileVelocity = 3000.0f;
	_aimingCameraOffset = FVector(50, 50, 50);

	_arrowSpawnCountArray.Add(1);
	_arrowSpawnCountArray.Add(3);
	_arrowSpawnCountArray.Add(5);
	_arrowSpawnCountArray.Add(7);
	_arrowSpawnCountArray.Add(9);
	_arrowSpawnCountArray.Add(11);
	_arrowSpawnCountSelectID = 0;

	_arrowIntervalArray.Add(2);
	_arrowIntervalArray.Add(6);
	_arrowIntervalArray.Add(10);
	_arrowIntervalSelectID = 0;

	_handRollArray.Add(0);
	_handRollArray.Add(0.5f);
	_handRollArray.Add(1.0f);
	_handRollSelectID = 0;
}

void ABowBase::VInitialize(ACreatureCharacter* weaponOwner)
{
	Super::VInitialize(weaponOwner);

	_characterCamera = Cast<ICharacterCameraInterface>(weaponOwner);
}

void ABowBase::BeginPlay()
{
	Super::BeginPlay();

	if(_crosshairWidgetClass)
	{
		_crosshairWidgetIns = NewObject<UCrosshairWidgetBase>(this, _crosshairWidgetClass);
	}
}

void ABowBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_animationModel.BowState = _bowState;
	_animationModel.bIsHoldingArrows = _holdingArrows.Num() > 0;
	_animationModel.HandRoll = _handRollArray[_handRollSelectID];

	UpdateArrowsTransform();
}

bool ABowBase::VTMCanFire()
{
	return (_characterAnimationState == EAnimationState::EAnimState_Walk || _characterAnimationState == EAnimationState::EAnimState_Fall )
			&& ( _bowState == EBowState::EBS_FullyDrawed || _bowState == EBowState::EBS_OverDrawing);
}

bool ABowBase::VTMCanAim()
{
	IActionInterface* actionInterface = Cast<IActionInterface>(GetWeaponOwner());

	bool bIsDodging = actionInterface ? actionInterface->VCheckActionIsInProgress(EActionType::EACT_Dodge) : false;

	return (_characterAnimationState == EAnimationState::EAnimState_Walk || _characterAnimationState == EAnimationState::EAnimState_Fall) && bIsDodging == false;
}

void ABowBase::VTMStartFiring()
{
	_bowState = EBowState::EBS_Released;
}

void ABowBase::VTMFiringInProgress(float deltaTime)
{
}

void ABowBase::VTMStopFiring()
{
}

void ABowBase::VTMStarAiming()
{
	ACreatureCharacter* weaponOwner = GetWeaponOwner();
	if(weaponOwner && weaponOwner->VGetAnimationModel().bIsSprinting == false)
	{
		weaponOwner->VSetCameraArmPitchLimit(-60, 60);
		weaponOwner->VDragCamera(_aimingCameraOffset);
		weaponOwner->VGetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, false);

		if(_crosshairWidgetIns)
		{
			_crosshairWidgetIns->AddToViewport(100);
		}
	}
}

void ABowBase::VTMAimingInProgress(float deltaTime)
{
	FRotator rotator = GetWeaponOwner()->VGetCameraRotation();
	rotator.Pitch = 0;
	rotator.Roll = 0;

	GetWeaponOwner()->SetActorRotation(rotator);
	AttachArrowsToHand();

	_strength = FMath::Clamp(_strength + deltaTime * _drawingVelocity, 0.0f, 1.0f);

	if (_crosshairWidgetIns)
	{
		_crosshairWidgetIns->Animate(deltaTime,true);
	}

}

void ABowBase::VTMStopAiming()
{
	_bowState = EBowState::EBS_Normal;
	_strength = 0.0f;

	if (_characterCamera)
	{
		_characterCamera->VResetCameraArmPitchLimit();
		_characterCamera->VCancelDragCamera();
	}

	if (_crosshairWidgetIns)
	{
		_crosshairWidgetIns->RemoveFromViewport();
	}

	//ClearHoldingArrows();
	GetWeaponOwner()->VGetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, true);
}

void ABowBase::VReset()
{
	Super::VReset();
}


void ABowBase::UpdateArrowsTransform()
{
	switch (_bowState)
	{
		case EBowState::EBS_Normal:
		{
			AttachArrowsToBow();
		}
		break;
		case EBowState::EBS_Drawing:
		case EBowState::EBS_FullyDrawed:
		case EBowState::EBS_OverDrawing:
		{
			AttachArrowsToHand();
		}
		break;
		case EBowState::EBS_Released:
			break;
		default:
			break;
	}
}

void ABowBase::AttachArrowsToHand()
{
	if (!_characterCamera) return;

	UCameraComponent* cameraComp = _characterCamera->VGetCameraComponent();
	if (!cameraComp) return;

	//Get Camera State
	FRotator cameraRotator = _characterCamera->VGetCameraRotation();
	FVector cameraLocation = cameraComp->GetComponentLocation();
	FVector cameraForward = cameraComp->GetForwardVector();

	//get arrow hit location using line tracing
	FHitResult hitResult;
	FCollisionQueryParams CollisionParams;
	FVector LineTraceStart = cameraLocation + cameraForward * _characterCamera->VGetCameraArmLength();
	FVector LineTraceEnd = cameraLocation + cameraForward * cameraComp->OrthoFarClipPlane;

	FVector hitLocation = LineTraceEnd;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, LineTraceStart, LineTraceEnd, ECC_Visibility, CollisionParams))
	{
		hitLocation = hitResult.ImpactPoint;
	}

	//get hand transform
	FTransform rightHandTransform;
	IMeshSocketTransformProvider* transformProvider = Cast<IMeshSocketTransformProvider>(GetWeaponOwner());
	if(transformProvider)
	{
		transformProvider->VTryGetMeshSocketTransform(EMeshSocketType::MST_RightHandDraw, ERelativeTransformSpace::RTS_World, rightHandTransform);
	}
	//get muzzle transform
	FTransform muzzleTransform;
	 VTryGetMeshSocketTransform(EMeshSocketType::MST_Muzzle,RTS_World, muzzleTransform);


	//compute Projectile Transform
	FVector projectileForward = muzzleTransform.GetLocation() - rightHandTransform.GetLocation();
	FVector dirToHitedLocation = hitLocation - rightHandTransform.GetLocation();

	FQuat projectileQuat = projectileForward.ToOrientationQuat();
	FQuat ToHitQuat = dirToHitedLocation.ToOrientationQuat();

	FVector muzzleLeft = muzzleTransform.GetRotation().RotateVector(FVector::LeftVector);
	

	float curDeltaDegree = 0;
	FQuat curDeltaQuat;

	for (int i = 0; i < _holdingArrows.Num(); ++i)
	{
		//compute quaternion
		curDeltaDegree = (i % 2) ? 
			_arrowIntervalArray[_arrowIntervalSelectID] * i 
				: _arrowIntervalArray[_arrowIntervalSelectID] * i * -1;

		curDeltaQuat = FQuat(muzzleLeft, FMath::DegreesToRadians(curDeltaDegree));
		projectileQuat = curDeltaQuat * projectileQuat;
		ToHitQuat = curDeltaQuat * ToHitQuat;
		
		//apply location,rotation
		if (_holdingArrows[i] != NULL)
		{
			_holdingArrows[i]->SetActorLocationAndRotation(rightHandTransform.GetLocation(), projectileQuat);
			_holdingArrows[i]->SetLaunchDirection(ToHitQuat.Vector());
		}
	}
}

void ABowBase::AttachArrowsToBow()
{
	//get muzzle transform
	FTransform muzzleTransform;
	FTransform bowStringTransform;

	VTryGetMeshSocketTransform(EMeshSocketType::MST_Muzzle, RTS_World, muzzleTransform);
	VTryGetMeshSocketTransform(EMeshSocketType::MST_BowString, RTS_World, bowStringTransform);

	FVector arrowForward = (muzzleTransform.GetLocation() - bowStringTransform.GetLocation()).GetSafeNormal();
	FQuat arrowQuat = arrowForward.ToOrientationQuat();

	FVector bowStringUp = bowStringTransform.GetRotation().RotateVector(FVector::UpVector);

	float curDeltaDegree = 0;
	FQuat curDeltaQuat;

	for (int i = 0; i < _holdingArrows.Num(); ++i)
	{
		//compute quaternion
		curDeltaDegree = (i % 2) ?
			_arrowIntervalArray[_arrowIntervalSelectID] * i 
				: _arrowIntervalArray[_arrowIntervalSelectID] * i * -1;

		curDeltaQuat = FQuat(bowStringUp, FMath::DegreesToRadians(curDeltaDegree));
		arrowQuat = curDeltaQuat * arrowQuat;

		//apply location,rotation
		if (_holdingArrows[i] != NULL)
		{
			_holdingArrows[i]->SetActorLocationAndRotation(bowStringTransform.GetLocation(), arrowQuat);
		}
	}
}

void ABowBase::OnEnterAnimFrame_ReleaseBowString()
{
	LaunchArrows();
	
	_bowState = EBowState::EBS_Released;
}

void ABowBase::OnEnterAnimFrame_ReloadCompleted()
{
	_bowState = EBowState::EBS_FullyDrawed;
}

FBowAnimationModelBase ABowBase::GetAnimationModel()
{
	return _animationModel;
}

void ABowBase::OnEnterAnimFrame_StartDrawingBowString()
{
	_bowState = EBowState::EBS_Drawing;
}

void ABowBase::OnEnterAnimFrame_TakeOutArrows()
{
	TakeOutArrows();
}


void ABowBase::ClearHoldingArrows()
{
	for (AArrowActorBase* arrow : _holdingArrows)
	{
		arrow->VSetIsActive(false);
	}
	_holdingArrows.Empty();
}

void ABowBase::LaunchArrows()
{
	for (AArrowActorBase* arrow : _holdingArrows)
	{
		arrow->Launch();
	}
	_holdingArrows.Empty();
}

void ABowBase::AdjustHandRotation()
{
	_handRollSelectID = (_handRollSelectID + 1) % _handRollArray.Num();
}

void ABowBase::AdjustArrowIntervals()
{
	_arrowIntervalSelectID = (_arrowIntervalSelectID + 1) % _arrowIntervalArray.Num();
}

void ABowBase::IncreaseArrows()
{
	_arrowSpawnCountSelectID = (_arrowSpawnCountSelectID + 1) % _arrowSpawnCountArray.Num();
	TakeOutArrows();
}

void ABowBase::DecreaseArrows()
{
	_arrowSpawnCountSelectID = (_arrowSpawnCountArray.Num() + _arrowSpawnCountSelectID - 1) % _arrowSpawnCountArray.Num();
	TakeOutArrows();
}

void ABowBase::VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState)
{
	Super::VOnCharacterAnimationStateChanged(prevState, newState);

	if(prevState == EAnimationState::EAnimState_Fall || prevState == EAnimationState::EAnimState_Walk)
	{
		if(newState!= EAnimationState::EAnimState_Fall && newState != EAnimationState::EAnimState_Walk)
		{
			StopAllActions();
		}
	}
}

void ABowBase::VWeaponControlButtonA()
{
	IncreaseArrows();
}

void ABowBase::VWeaponControlButtonB()
{
	DecreaseArrows();
}

void ABowBase::VWeaponControlButtonC()
{
	AdjustHandRotation();
}

void ABowBase::VWeaponControlButtonD()
{
	AdjustArrowIntervals();
}

float ABowBase::_CalculateDamage()
{
	return _strength * _maxDamage;
}

float ABowBase::_CalculateProjectileSpeed()
{
	return FMath::Clamp(_strength * _maxProjectileVelocity, _baseProjectileVelocity, _maxProjectileVelocity);
}

EBowState ABowBase::GetBowState()
{
	return _bowState;
}

void ABowBase::TakeOutArrows()
{
	ClearHoldingArrows();
	if (_holdingArrows.Num() == 0) 
	{
		_quiverComponent->SpawnArrows(_arrowSpawnCountArray[_arrowSpawnCountSelectID], GetWeaponOwner(), _holdingArrows);
	}
}
