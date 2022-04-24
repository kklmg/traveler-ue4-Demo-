// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BowBase.h"
#include "Actors/ArrowActorBase.h"
#include "Character/CreatureCharacter.h"
#include "Components/PawnCameraComponent.h"
#include "Components/QuiverComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Command/CommandActor.h"
#include "Interface/CharacterCameraInterface.h"
#include "UI/CrosshairWidgetBase.h"
#include "GameSystem/DebugMessageHelper.h"
#include "Data/WeaponAnimationModelBase.h"
#include "GameSystem/OptionBase.h"
#include "Enums/EnumAnimation.h"

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
	_baseProjectileVelocity = 1000.0f;
	_maxProjectileVelocity = 3000.0f;
	_aimingCameraOffset = FVector(50, 50, 50);
}

void ABowBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	_processFire = NewObject<UBowProcessFire>(this);
	_processFire->VSetWeapon(this);
	_processFire->ProcessStateChangedDelegate.AddUObject(this, &ABowBase::OnFireProcessChanged);
	AddToProcessMap(_processFire);

	_processAim = NewObject<UBowProcessAim>(this);
	_processAim->VSetWeapon(this);
	_processAim->ProcessStateChangedDelegate.AddUObject(this, &ABowBase::OnAimProcessChanged);
	AddToProcessMap(_processAim);

	if (GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->WeaponType = _weaponType;
	}

	_arrowCountOptionIns = _arrowCountOptionClass ?
		NewObject<UIntOption>(this, _arrowCountOptionClass) : NewObject<UIntOption>(this);

	_arrowIntervalOptionIns = _arrowIntervalOptionClass ?
		NewObject<UFloatOption>(this, _arrowIntervalOptionClass) : NewObject<UFloatOption>(this);

	_wristRollOptionIns = _wristRollOptionClass ?
		NewObject<UFloatOption>(this, _wristRollOptionClass) : NewObject<UFloatOption>(this);
}

void ABowBase::VInitialize(ACreatureCharacter* weaponOwner)
{
	Super::VInitialize(weaponOwner);
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

	UEventBrokerComponent* eventBrokerComp = GetOwnerEventBrokerComp();

	if (eventBrokerComp)
	{
		FDelegateHandle delegateHandle;

		delegateHandle = eventBrokerComp->
				GetEventDelegate(NSNameBowAnimEvent::Bow_DrawingBowString).AddUObject(this, &ABowBase::OnAnim_StartDrawingBowString);
		_delegateHandles.Add(FDelegateHandleData(NSNameBowAnimEvent::Bow_DrawingBowString,delegateHandle));

		delegateHandle = eventBrokerComp->
			GetEventDelegate(NSNameBowAnimEvent::Bow_TakeOutArrows).AddUObject(this, &ABowBase::OnAnim_TakeOutArrows);
		_delegateHandles.Add(FDelegateHandleData(NSNameBowAnimEvent::Bow_TakeOutArrows, delegateHandle));

		delegateHandle = eventBrokerComp->
			GetEventDelegate(NSNameBowAnimEvent::Bow_FullyDrawed).AddUObject(this, &ABowBase::OnAnim_FullyDrawed);
		_delegateHandles.Add(FDelegateHandleData(NSNameBowAnimEvent::Bow_FullyDrawed, delegateHandle));

		delegateHandle = eventBrokerComp->
			GetEventDelegate(NSNameBowAnimEvent::Bow_ReleasedBowString).AddUObject(this, &ABowBase::OnAnim_ReleaseBowString);
		_delegateHandles.Add(FDelegateHandleData(NSNameBowAnimEvent::Bow_ReleasedBowString, delegateHandle));
	}

	auto weaponAnimationModel = GetWeaponAnimationModel();
	if(weaponAnimationModel)
	{
		weaponAnimationModel->SetBool(NSNameAnimData::bArrowsSpawned, false);
		weaponAnimationModel->SetUInt8(NSNameAnimData::byteBowState, (uint8)_bowState);
		weaponAnimationModel->SetBool(NSNameAnimData::bIsDrawingBow, IsDrawingBow());
		weaponAnimationModel->SetFloat(NSNameAnimData::fWristRoll, _wristRollOptionIns->GetSelection());
		weaponAnimationModel->SetBool(NSNameAnimData::bIsFiring, IsProcessRunning(NSNameWeaponProcess::FIRE));
		weaponAnimationModel->SetBool(NSNameAnimData::bIsAiming, IsProcessRunning(NSNameWeaponProcess::AIM));
	}
}


void ABowBase::VOnUnEquipped()
{
	Super::VOnUnEquipped();

	UEventBrokerComponent* eventBrokerComp = GetOwnerEventBrokerComp();

	if (eventBrokerComp)
	{
		FMD_OnEventPublished outEventPublishedDelegate;
		for (auto delegateHandleData : _delegateHandles)
		{
			eventBrokerComp->GetEventDelegate(delegateHandleData.EventName).Remove(delegateHandleData.DelegateHandle);
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
	if(GetOwnerExTransformProviderComp())
	{
		GetOwnerExTransformProviderComp()->TryGetTransform(ETransform::ETransform_RightHandDraw, ERelativeTransformSpace::RTS_World, rightHandTransform);
	}
	//get muzzle transform
	FTransform muzzleTransform;
	GetExTransformProviderComp()->TryGetTransform(ETransform::ETransform_Muzzle, RTS_World, muzzleTransform);

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
			_arrowIntervalOptionIns->GetSelection() * i
				: _arrowIntervalOptionIns->GetSelection() * i * -1;

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

	GetExTransformProviderComp()->TryGetTransform(ETransform::ETransform_Muzzle, RTS_World, muzzleTransform);
	GetExTransformProviderComp()->TryGetTransform(ETransform::ETransform_BowString, RTS_World, bowStringTransform);

	FVector arrowForward = (muzzleTransform.GetLocation() - bowStringTransform.GetLocation()).GetSafeNormal();
	FQuat arrowQuat = arrowForward.ToOrientationQuat();

	FVector bowStringUp = bowStringTransform.GetRotation().RotateVector(FVector::UpVector);

	float curDeltaDegree = 0;
	FQuat curDeltaQuat;

	for (int i = 0; i < _holdingArrows.Num(); ++i)
	{
		//compute quaternion
		curDeltaDegree = (i % 2) ?
			_arrowIntervalOptionIns->GetSelection() * i
				: _arrowIntervalOptionIns->GetSelection() * i * -1;

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
		GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsFiring, IsProcessRunning(NSNameWeaponProcess::FIRE));
	}
}

void ABowBase::OnAimProcessChanged(EProcessState processState)
{
	if (GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsAiming, IsProcessRunning(NSNameWeaponProcess::AIM));
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
		GetWeaponAnimationModel()->SetBool(NSNameAnimData::bArrowsSpawned, false);
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
	_wristRollOptionIns->Scroll(1);

	if (GetWeaponAnimationModel())
	{
		GetWeaponAnimationModel()->SetFloat(NSNameAnimData::fWristRoll, _wristRollOptionIns->GetSelection());
	}
}

void ABowBase::AdjustArrowIntervals()
{
	_arrowIntervalOptionIns->Scroll(1);
}

void ABowBase::IncreaseArrows()
{
	_arrowCountOptionIns->Scroll(1);
	ClearHoldingArrows(true);
	SetBowState(EBowState::EBS_Normal);
}

void ABowBase::DecreaseArrows()
{
	_arrowCountOptionIns->Scroll(-1);
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

void ABowBase::OnAnim_StartDrawingBowString(UObject* data)
{
	SetBowState(EBowState::EBS_Drawing);
}

void ABowBase::OnAnim_TakeOutArrows(UObject* data)
{
	TakeOutArrows();
}

void ABowBase::OnAnim_ReleaseBowString(UObject* data)
{
	LaunchArrows();
	SetBowState(EBowState::EBS_ReleaseEnd);
}

void ABowBase::OnAnim_FullyDrawed(UObject* data)
{
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
		GetWeaponAnimationModel()->SetUInt8(NSNameAnimData::byteBowState, (uint8)_bowState);
		GetWeaponAnimationModel()->SetBool(NSNameAnimData::bIsDrawingBow, IsDrawingBow());
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
	
	if(_quiverComponent->SpawnArrows(_arrowCountOptionIns->GetSelection(), GetWeaponOwner(), _holdingArrows))
	{
		if (GetWeaponAnimationModel())
		{
			GetWeaponAnimationModel()->SetBool(NSNameAnimData::bArrowsSpawned, true);
		}
	}
}
