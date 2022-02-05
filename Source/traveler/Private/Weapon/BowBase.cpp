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

	_holdCount = 5;
	_ProjectilesInterval = 2;
}

void ABowBase::VInitialize(ACreatureCharacter* weaponOwner)
{
	Super::VInitialize(weaponOwner);

	_characterCamera = Cast<ICharacterCameraInterface>(weaponOwner);
}

void ABowBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABowBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_animationModel.BowState = _bowState;
}

bool ABowBase::VTMCanFire()
{
	return _bowState == EBowState::EBS_FullyDrawed || _bowState == EBowState::EBS_OverDrawing;
}

bool ABowBase::VTMCanAim()
{
	return true;
}

void ABowBase::VTMStartFiring()
{
	/*if (_characterCamera)
	{
		FRotator rotator = _characterCamera->VGetCameraRotation();
		rotator.Pitch = 0;
		rotator.Roll = 0;

		GetWeaponOwner()->SetActorRotation(rotator);
	}*/
	if (_bowState == EBowState::EBS_FullyDrawed || _bowState == EBowState::EBS_OverDrawing)
	{
		_bowState = EBowState::EBS_Released;
	}
}

void ABowBase::VTMFiringInProgress(float deltaTime)
{
}

void ABowBase::VTMStopFiring()
{
}

void ABowBase::VTMStarAiming()
{
	GetWeaponOwner()->VSetCameraArmPitchLimit(-60, 60);
	GetWeaponOwner()->VDragCamera(_aimingCameraOffset);

	GetWeaponOwner()->VGetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection,false);
}

void ABowBase::VTMAimingInProgress(float deltaTime)
{
	FRotator rotator = GetWeaponOwner()->VGetCameraRotation();
	rotator.Pitch = 0;
	rotator.Roll = 0;

	GetWeaponOwner()->SetActorRotation(rotator);
	_UpdateProjectilesTransform(_ProjectilesInterval);

	_strength = FMath::Clamp(_strength + deltaTime * _drawingVelocity, 0.0f, 1.0f);
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

	ClearHoldingArrows();
	GetWeaponOwner()->VGetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, true);
}


void ABowBase::_UpdateProjectilesTransform(float deltaDegree)
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

	//get transform of muzzle and hand
	FTransform rightHandTransform;
	FTransform muzzleTransform;
	IMeshSocketTransformProvider* transformProvider = Cast<IMeshSocketTransformProvider>(GetWeaponOwner());
	if(transformProvider)
	{
		transformProvider->VTryGetMeshSocketTransform(EMeshSocketType::MST_RightHandDraw, ERelativeTransformSpace::RTS_World, rightHandTransform);
	}
	muzzleTransform = GetMuzzleTransform();


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
		curDeltaDegree = (i % 2) ? deltaDegree * i  : deltaDegree * i*-1;
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
	HoldArrows(_holdCount);
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

void ABowBase::HoldArrows(int count)
{
	ClearHoldingArrows();
	_quiverComponent->SpawnArrows(count, GetWeaponOwner(), _holdingArrows);
}

FTransform ABowBase::GetMuzzleTransform()
{
	return  GetMeshComponent()->GetSocketTransform(_meshSocketMuzzle, ERelativeTransformSpace::RTS_World);
}