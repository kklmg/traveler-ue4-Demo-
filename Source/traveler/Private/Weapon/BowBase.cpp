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
#include "Interface/ExtraTransformProvider.h"
#include "Interface/ActionInterface.h"
#include "UI/CrosshairWidgetBase.h"
#include "GameSystem/DebugMessageHelper.h"
#include "Data/WeaponAnimationModelBase.h"

#include "Weapon/WeaponProcess/BowProcess/BowProcessFire.h"
#include "Weapon/WeaponProcess/BowProcess/BowProcessAim.h"

ABowBase::ABowBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Create quiver component used in projectile management
	if (_quiverComponent == nullptr)
	{
		_quiverComponent = CreateDefaultSubobject<UQuiverComponent>(TEXT("QuiverComponent"));
		check(_quiverComponent != nullptr);
	}

	_weaponType	= EWeaponType::EWT_Bow;
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

	_processFire = NewObject<UBowProcessFire>(this);
	_processFire->VSetWeapon(this);
	_processFire->OnProcessStateChanged.AddUObject(this, &ABowBase::OnFireProcessChanged);
	AddToProcessStorage(_processFire);

	_processAim = NewObject<UBowProcessAim>(this);
	_processAim->VSetWeapon(this);
	_processAim->OnProcessStateChanged.AddUObject(this, &ABowBase::OnAimProcessChanged);
	AddToProcessStorage(_processAim);

	if (GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->WeaponType = _weaponType;
	}
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

	if (_crosshairWidgetIns)
	{
		_crosshairWidgetIns->Animate(DeltaTime);
	}
	UpdateArrowsTransform();
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
		case EBowState::EBS_ReleaseStart:
		{
			AttachArrowsToHand();
		}
		break;
		case EBowState::EBS_ReleaseEnd:
			break;
		default:
			break;
	}
}

void ABowBase::SetStrength(float elapsedTime)
{
	_strength = FMath::Clamp(elapsedTime * _drawingVelocity, 0.1f, 1.5f);
}

bool ABowBase::IsDrawingBow()
{
	switch (_bowState)
	{
		case EBowState::EBS_Drawing:
		case EBowState::EBS_FullyDrawed:
		case EBowState::EBS_OverDrawing:
		case EBowState::EBS_ReleaseStart:
		{
			return true;
		}
		break;
		case EBowState::EBS_Normal:
		case EBowState::EBS_ReleaseEnd:
		default:
		{
			return false; 
		}
		break;
	}
}

void ABowBase::VOnEquipped()
{
	Super::VOnEquipped();

	IEventBrokerInterface* eventBrokerInterface = GetEventBrokerInterface();

	if (eventBrokerInterface)
	{
		FDelegateHandle delegateHandle;

		delegateHandle = eventBrokerInterface->
				VGetEventDelegate(BowAnimEventName::Bow_DrawingBowString).AddUObject(this, &ABowBase::OnAnim_StartDrawingBowString);
		_delegateHandles.Add(FDelegateHandleData(BowAnimEventName::Bow_DrawingBowString,delegateHandle));

		delegateHandle = eventBrokerInterface->
			VGetEventDelegate(BowAnimEventName::Bow_TakeOutArrows).AddUObject(this, &ABowBase::OnAnim_TakeOutArrows);
		_delegateHandles.Add(FDelegateHandleData(BowAnimEventName::Bow_TakeOutArrows, delegateHandle));

		delegateHandle = eventBrokerInterface->
			VGetEventDelegate(BowAnimEventName::Bow_FullyDrawed).AddUObject(this, &ABowBase::OnAnim_FullyDrawed);
		_delegateHandles.Add(FDelegateHandleData(BowAnimEventName::Bow_FullyDrawed, delegateHandle));

		delegateHandle = eventBrokerInterface->
			VGetEventDelegate(BowAnimEventName::Bow_ReleasedBowString).AddUObject(this, &ABowBase::OnAnim_ReleaseBowString);
		_delegateHandles.Add(FDelegateHandleData(BowAnimEventName::Bow_ReleasedBowString, delegateHandle));
	}

	auto weaponAnimationModel = GetWeaponAnimationModel();
	if(weaponAnimationModel)
	{
		weaponAnimationModel->SetBool(WeaponAnimationDataKey::bArrowsSpawned, false);
		weaponAnimationModel->SetUInt8(WeaponAnimationDataKey::byteBowState, (uint8)_bowState);
		weaponAnimationModel->SetBool(WeaponAnimationDataKey::bIsDrawingBow, IsDrawingBow());
		weaponAnimationModel->SetFloat(WeaponAnimationDataKey::fHandRoll, _handRollArray[_handRollSelectID]);
		weaponAnimationModel->SetBool(WeaponAnimationDataKey::bIsFiring, IsProcessRunning(WeaponProcessName::FIRE));
		weaponAnimationModel->SetBool(WeaponAnimationDataKey::bIsAiming, IsProcessRunning(WeaponProcessName::AIM));
	}
}


void ABowBase::VOnUnEquipped()
{
	Super::VOnUnEquipped();

	IEventBrokerInterface* eventBrokerInterface = GetEventBrokerInterface();

	if (eventBrokerInterface)
	{
		FMD_OnEventPublished outEventPublishedDelegate;
		for (auto delegateHandleData : _delegateHandles)
		{
			eventBrokerInterface->VGetEventDelegate(delegateHandleData.EventName).Remove(delegateHandleData.DelegateHandle);
		}
	}

	auto weaponAnimationModel = GetWeaponAnimationModel();
	if (weaponAnimationModel)
	{
		weaponAnimationModel->ClearData();
	}

	_delegateHandles.Empty();
}

void ABowBase::AttachArrowsToHand()
{
	ICharacterCameraInterface* cameraInterface = GetOwnerCameraInterface();
	if (!cameraInterface) return;

	UCameraComponent* cameraComp = cameraInterface->VGetCameraComponent();
	if (!cameraComp) return;

	//Get Camera State
	FRotator cameraRotator = cameraInterface->VGetCameraRotation();
	FVector cameraLocation = cameraComp->GetComponentLocation();
	FVector cameraForward = cameraComp->GetForwardVector();

	//get arrow hit location using line tracing
	FHitResult hitResult;
	FCollisionQueryParams CollisionParams;
	FVector LineTraceStart = cameraLocation + cameraForward * cameraInterface->VGetCameraArmLength();
	FVector LineTraceEnd = cameraLocation + cameraForward * cameraComp->OrthoFarClipPlane;

	FVector hitLocation = LineTraceEnd;
	
	//Execute line Tracing
	bool bHitted = false;
	bHitted = GetWorld()->LineTraceSingleByChannel(hitResult, LineTraceStart, LineTraceEnd, ECC_Visibility, CollisionParams);

	if (bHitted)
	{
		hitLocation = hitResult.ImpactPoint;
	}

	if (_crosshairWidgetIns)
	{
		_crosshairWidgetIns->SetIsOnTarget(bHitted);
	}


	//get hand transform
	FTransform rightHandTransform;
	IExtraTransformProvider* transformProvider = Cast<IExtraTransformProvider>(GetWeaponOwner());
	if(transformProvider)
	{
		transformProvider->VTryGetTransform(ETransform::ETransform_RightHandDraw, ERelativeTransformSpace::RTS_World, rightHandTransform);
	}
	//get muzzle transform
	FTransform muzzleTransform;
	 VTryGetTransform(ETransform::ETransform_Muzzle,RTS_World, muzzleTransform);


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

	VTryGetTransform(ETransform::ETransform_Muzzle, RTS_World, muzzleTransform);
	VTryGetTransform(ETransform::ETransform_BowString, RTS_World, bowStringTransform);

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

void ABowBase::OnFireProcessChanged(EProcessState processState)
{
	if (GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->SetBool(WeaponAnimationDataKey::bIsFiring, IsProcessRunning(WeaponProcessName::FIRE));
	}
}

void ABowBase::OnAimProcessChanged(EProcessState processState)
{
	if (GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->SetBool(WeaponAnimationDataKey::bIsAiming, IsProcessRunning(WeaponProcessName::AIM));
	}
}

void ABowBase::ClearHoldingArrows(bool bDeactivateArrows)
{
	if (_holdingArrows.Num() == 0) return;

	if(bDeactivateArrows)
	{
		for (AArrowActorBase* arrow : _holdingArrows)
		{
			arrow->VInActivate();
		}
	}
	_holdingArrows.Empty();

	if(GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->SetBool(WeaponAnimationDataKey::bArrowsSpawned, false);
	}
}

void ABowBase::LaunchArrows()
{
	for (AArrowActorBase* arrow : _holdingArrows)
	{
		arrow->Launch();
	}

	ClearHoldingArrows(false);
}

void ABowBase::AdjustHandRotation()
{
	_handRollSelectID = (_handRollSelectID + 1) % _handRollArray.Num();

	if (GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->SetFloat(WeaponAnimationDataKey::fHandRoll, _handRollArray[_handRollSelectID]);
	}
}

void ABowBase::AdjustArrowIntervals()
{
	_arrowIntervalSelectID = (_arrowIntervalSelectID + 1) % _arrowIntervalArray.Num();
}

void ABowBase::IncreaseArrows()
{
	_arrowSpawnCountSelectID = (_arrowSpawnCountSelectID + 1) % _arrowSpawnCountArray.Num();
	ClearHoldingArrows(true);
	SetBowState(EBowState::EBS_Normal);
}

void ABowBase::DecreaseArrows()
{
	_arrowSpawnCountSelectID = (_arrowSpawnCountArray.Num() + _arrowSpawnCountSelectID - 1) % _arrowSpawnCountArray.Num();
	ClearHoldingArrows(true);
	SetBowState(EBowState::EBS_Normal);
}

void ABowBase::VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState)
{
	Super::VOnCharacterAnimationStateChanged(prevState, newState);

	if(prevState == EAnimationState::EAnimState_Fall || prevState == EAnimationState::EAnimState_Walk)
	{
		if(newState!= EAnimationState::EAnimState_Fall && newState != EAnimationState::EAnimState_Walk)
		{
			StopAllProcesses();
		}
	}
}

void ABowBase::OnAnim_StartDrawingBowString(UEventDataBase* eventData)
{
	if (IsProcessRunning(WeaponProcessName::AIM) == false) return;
	SetBowState(EBowState::EBS_Drawing);
}

void ABowBase::OnAnim_TakeOutArrows(UEventDataBase* eventData)
{
	TakeOutArrows();
}

void ABowBase::OnAnim_ReleaseBowString(UEventDataBase* eventData)
{
	if (IsProcessRunning(WeaponProcessName::AIM) == false) return;

	LaunchArrows();
	SetBowState(EBowState::EBS_ReleaseEnd);
}

void ABowBase::OnAnim_FullyDrawed(UEventDataBase* eventData)
{
	if (IsProcessRunning(WeaponProcessName::AIM) == false) return;
	SetBowState(EBowState::EBS_FullyDrawed);
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

float ABowBase::CalculateDamage()
{
	return _strength * _maxDamage;
}

float ABowBase::CalculateProjectileSpeed()
{
	return FMath::Clamp(_strength * _maxProjectileVelocity, _baseProjectileVelocity, _maxProjectileVelocity);
}

EBowState ABowBase::GetBowState()
{
	return _bowState;
}

bool ABowBase::SetBowState(EBowState bowState)
{
	if (_bowState == bowState) return false;

	_bowState = bowState;
	if(GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->SetUInt8(WeaponAnimationDataKey::byteBowState, (uint8)_bowState);
		GetWeaponAnimationModel()->SetBool(WeaponAnimationDataKey::bIsDrawingBow, IsDrawingBow());
	}
	return true;
}

void ABowBase::DragCamera(bool bDrag)
{
	ICharacterCameraInterface* cameraInterface = GetOwnerCameraInterface();
	if (!cameraInterface) return;

	if (bDrag) 
	{
		cameraInterface->VSetCameraArmPitchLimit(-60, 60);
		cameraInterface->VDragCamera(_aimingCameraOffset);
	}
	else
	{
		cameraInterface->VResetCameraArmPitchLimit();
		cameraInterface->VCancelDragCamera();
	}
}

void ABowBase::AnimateCrosshair(bool bForward)
{
	if (!_crosshairWidgetIns) return;
	_crosshairWidgetIns->SetAnimForward(bForward);
}

void ABowBase::TakeOutArrows()
{
	ClearHoldingArrows(true);

	if(_quiverComponent->SpawnArrows(_arrowSpawnCountArray[_arrowSpawnCountSelectID], GetWeaponOwner(), _holdingArrows))
	{
		if (GetWeaponAnimationModel())
		{
			GetWeaponAnimationModel()->SetBool(WeaponAnimationDataKey::bArrowsSpawned, true);
		}
	}
}
