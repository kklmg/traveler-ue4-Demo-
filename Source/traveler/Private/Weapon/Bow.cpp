// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bow.h"
#include "Projectile/Projectile.h"
#include "Character/CreatureCharacter.h"
#include "Components/PawnCameraComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Command/CommandActor.h"
#include "Interface/CharacterCameraInterface.h"

ABow::ABow() 
{
	WeaponType = EWeaponType::WT_Bow;

	_isAiming = false;
	_strength = 0.0f;
	_maxDamage = 0.0f;
	_drawingVelocity = 0.5f;
	_baseProjectileVelocity = 1000.0f;
	_maxProjectileVelocity = 3000.0f;
	_aimingCameraOffset = FVector(100, 0, 100);

	_spawnProjectileCount = 5;
	_ProjectilesInterval = 2;
}


void ABow::VInitialize(ACreatureCharacter* weaponOwner)
{
	Super::VInitialize(weaponOwner);

	_characterCamera = Cast<ICharacterCameraInterface>(weaponOwner);

	if (_aimButtonCommandClass)
	{
		_aimButtonCommand = NewObject<UCommandActor>(this, _aimButtonCommandClass);
		_aimButtonCommand->Initialize(weaponOwner);
	}

}

void ABow::BeginPlay()
{
	Super::BeginPlay();
}

void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isAiming)
	{
		_strength = FMath::Clamp(_strength + DeltaTime * _drawingVelocity, 0.0f, 1.0f);
	}
}

void ABow::OnFireButtonDown()
{
	if (_isAiming == false && _characterCamera)
	{
		FRotator rotator = _characterCamera->VGetCameraRotation();
		rotator.Pitch = 0;
		rotator.Roll = 0;

		GetWeaponOwner()->SetActorRotation(rotator);
	}
}
void ABow::OnFireButtonPress(float deltaTime)
{
	//UGameplayStatics::PredictProjectilePath();

	//FiringInProgress();


}
void ABow::OnFireButtonUp()
{
	//_SpawnProjectile();

	//if (_fireAnimMontage != nullptr)
	//{
	//	//_fireAnimMontage->noti
	//	//GetWeaponOwner()->PlayAnimMontage(_fireAnimMontage, 1.0f, TEXT("Release"));
	//}
}

void ABow::OnAimButtonDown()
{
	_isAiming = true;

	GetWeaponOwner()->VSetCameraArmPitchLimit(-60, 60);
	GetWeaponOwner()->VDragCamera(_aimingCameraOffset);

	if (_aimButtonCommand) 
	{
		_aimButtonCommand->VExecute();
	}
}

void ABow::OnAimButtonPress(float deltaTime)
{
	FRotator rotator = GetWeaponOwner()->VGetCameraRotation();
	rotator.Pitch = 0;
	rotator.Roll = 0;

	GetWeaponOwner()->SetActorRotation(rotator);

	_UpdateProjectileTransform(_ProjectilesInterval);
}
void ABow::OnAimButtonUp()
{
	_isAiming = false;
	_isDrawing = false;
	_strength = 0.0f;

	if(_characterCamera)
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

	
	_arraySpawnedProjectiles.Empty();
}


//void ABow::OnCharacterStateChanged(ECharacterState characterState)
//{
//	if (characterState == ECharacterState::CS_GroundNormal) 
//	{
//		OnAimButtonUp();
//	}
//}

void ABow::_UpdateProjectileTransform(float deltaDegree) 
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
	GetWeaponOwner()->GetMeshSocketTransform(EMeshSocketType::MST_RightHandDraw, ERelativeTransformSpace::RTS_World, rightHandTransform);
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

void ABow::OnEnterAnimFrame_ReloadStart()
{
	Super::OnEnterAnimFrame_ReloadStart();
}

void ABow::OnTickAnimFrame_Reloading() 
{
}

void ABow::OnEnterAnimFrame_ReloadCompleted()
{
}

void ABow::OnEnterAnimFrame_Launch()
{
	
	for (auto projectile : _arraySpawnedProjectiles) 
	{
		if (projectile) 
		{
			projectile->Launch(5000);

			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("launched projectile"));
		}
	}
	_arraySpawnedProjectiles.Empty();
	
	_isDrawing = false;
}

void ABow::OnEnterAnimFrame_StartDrawingBow()
{
	_isDrawing = true;
}

void ABow::OnEnterAnimFrame_GrabArrow() 
{
	//_SpawnProjectile(5);
	_SpawnProjectile(_spawnProjectileCount);
}


void ABow::AddProjectile(AProjectile* projectile) 
{
	_projectiles.Add(projectile);
}

void ABow::_SpawnProjectile(int count)
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


float ABow::_CalculateDamage() 
{
	return _strength * _maxDamage;
}

float ABow::_CalculateProjectileSpeed()
{
	return FMath::Clamp(_strength * _maxProjectileVelocity, _baseProjectileVelocity, _maxProjectileVelocity);
}

bool ABow::isDrawing() 
{
	return _isDrawing;
}

FTransform ABow::GetMuzzleTransform() 
{
	return  GetMeshComponent()->GetSocketTransform(_meshSocketMuzzle, ERelativeTransformSpace::RTS_World);
}