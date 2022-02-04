// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BowBase.h"
#include "Projectile/Projectile.h"
#include "Character/CreatureCharacter.h"
#include "Components/PawnCameraComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Command/CommandActor.h"
#include "Interface/CharacterCameraInterface.h"
#include "Interface/MeshSocketTransformProvider.h"

ABowBase::ABowBase()
{
	WeaponType = EWeaponType::EWT_Bow;
	_bowState = EBowState::EBS_Normal;

	_strength = 0.0f;
	_maxDamage = 0.0f;
	_drawingVelocity = 0.5f;
	_baseProjectileVelocity = 1000.0f;
	_maxProjectileVelocity = 3000.0f;
	_aimingCameraOffset = FVector(50, 50, 50);

	_spawnProjectileCount = 5;
	_ProjectilesInterval = 2;
}

void ABowBase::VInitialize(ACreatureCharacter* weaponOwner)
{
	Super::VInitialize(weaponOwner);

	_characterCamera = Cast<ICharacterCameraInterface>(weaponOwner);

	if (_aimButtonCommandClass)
	{
		_aimButtonCommand = NewObject<UCommandActor>(this, _aimButtonCommandClass);
		_aimButtonCommand->Initialize(weaponOwner);
	}
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

	_LaunchProjectiles();
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
	GetWeaponOwner()->VSetCameraArmPitchLimit(-60, 60);
	GetWeaponOwner()->VDragCamera(_aimingCameraOffset);

	GetWeaponOwner()->VGetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection,false);

	if (_aimButtonCommand)
	{
		_aimButtonCommand->VExecute();
	}
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

	for (auto projectile : _arraySpawnedProjectiles)
	{
		projectile->Destroy();
	}

	if (_aimButtonCommand)
	{
		_aimButtonCommand->VUndo();
	}

	_bowState = EBowState::EBS_Normal;

	_arraySpawnedProjectiles.Empty();

	GetWeaponOwner()->VGetActionBlackBoard()->WriteData_Bool(EActionDataKey::EACTD_TurnToMovingDirection, true);
}


void ABowBase::_UpdateProjectilesTransform(float deltaDegree)
{
	if (!_characterCamera) return;

	UCameraComponent* cameraComp = _characterCamera->VGetCameraComponent();
	if (!cameraComp) return;

	//Get Camera Rotator
	FRotator cameraRotator = _characterCamera->VGetCameraRotation();
	
	//do line tracing
	FHitResult hitResult;
	FCollisionQueryParams CollisionParams;
	FVector LineTraceStart = cameraComp->GetComponentLocation() + cameraComp->GetForwardVector() * _characterCamera->VGetCameraArmLength();
	FVector farPlaneCenter = cameraComp->GetComponentLocation() + cameraComp->GetForwardVector() * cameraComp->OrthoFarClipPlane;
	FVector hitLocation = farPlaneCenter;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, LineTraceStart, farPlaneCenter, ECC_Visibility, CollisionParams))
	{
		hitLocation = hitResult.ImpactPoint;
	}
	else
	{
		//hitLocation = cameraComp->GetComponentLocation() + cameraComp->GetForwardVector() * 1500;
		hitLocation = farPlaneCenter;
	}


	//--------------------------------------------------------------------------------------------------------------------


	//get weapon,hand transform
	FTransform rightHandTransform, muzzleTransform;

	IMeshSocketTransformProvider* transformProvider = Cast<IMeshSocketTransformProvider>(GetWeaponOwner());
	if(transformProvider)
	{
		transformProvider->VTryGetMeshSocketTransform(EMeshSocketType::MST_RightHandDraw, ERelativeTransformSpace::RTS_World, rightHandTransform);
	}

	muzzleTransform = GetMuzzleTransform();

	//compute Projectile Transform
	FVector projectileForward = muzzleTransform.GetLocation() - rightHandTransform.GetLocation();
	FVector dirToHit = hitLocation - rightHandTransform.GetLocation();


	FQuat projectileQuat = projectileForward.ToOrientationQuat();
	FQuat ToHitQuat = dirToHit.ToOrientationQuat();

	FVector weaponLeft = muzzleTransform.GetRotation().RotateVector(FVector::LeftVector);
	

	float curDeltaDegree = 0;
	FQuat curDeltaQuat;

	for (int i = 0; i < _arraySpawnedProjectiles.Num(); ++i)
	{
		//compute quaternion
		curDeltaDegree = (i % 2) ? deltaDegree * i  : deltaDegree * i*-1;
		curDeltaQuat = FQuat(weaponLeft, FMath::DegreesToRadians(curDeltaDegree));


		projectileQuat = curDeltaQuat * projectileQuat;
		ToHitQuat = curDeltaQuat * ToHitQuat;
		
		//apply location,rotation
		if (_arraySpawnedProjectiles[i] != NULL)
		{
			_arraySpawnedProjectiles[i]->SetActorLocationAndRotation(rightHandTransform.GetLocation(), projectileQuat);
			_arraySpawnedProjectiles[i]->SetFlyingDirection(ToHitQuat.Vector());
		}
	}
}

void ABowBase::OnEnterAnimFrame_ReleaseBowString()
{
	_LaunchProjectiles();
	
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
	_SpawnProjectiles(_spawnProjectileCount);
}


void ABowBase::AddProjectile(AProjectile* projectile)
{
	_projectiles.Add(projectile);
}

void ABowBase::_SpawnProjectiles(int count)
{
	int needSpawn = count - _arraySpawnedProjectiles.Num();

	if (needSpawn < 1) return;
	//Spawn Projectile
	UWorld* World = GetWorld();

	// Attempt to fire a projectile.
	if (ProjectileClass && World)
	{
		//set spawnParameter
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetWeaponOwner();

		for (int i = 0; i < needSpawn; ++i)
		{
			AProjectile* projectile = World->SpawnActor<AProjectile>(ProjectileClass,SpawnParams);
			_arraySpawnedProjectiles.Add(projectile);
		}
	}
}

void ABowBase::_LaunchProjectiles()
{
	for (auto projectile : _arraySpawnedProjectiles)
	{
		if (projectile)
		{
			projectile->Launch(5000);
		}
	}
	_arraySpawnedProjectiles.Empty();
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

FTransform ABowBase::GetMuzzleTransform()
{
	return  GetMeshComponent()->GetSocketTransform(_meshSocketMuzzle, ERelativeTransformSpace::RTS_World);
}