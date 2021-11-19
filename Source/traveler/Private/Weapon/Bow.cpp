// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bow.h"
#include "Projectile/Projectile.h"
#include "Character/MyCharacter.h"
#include "Components/PawnCameraComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CameraSpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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
	if (_isAiming == false)
	{
		UPawnCameraComponent* cameraComponent = GetWeaponOwner()->GetCameraComponent();

		FRotator rotator = cameraComponent->GetComponentRotation();
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

	UCameraSpringArmComponent* CameraSpringArmComponent = GetWeaponOwner()->GetSpringArmComponent();
	UPawnCameraComponent* cameraComponent = GetWeaponOwner()->GetCameraComponent();

	CameraSpringArmComponent->SetPitchRange(-60, 60);
	cameraComponent->BeginDragCamera(_aimingCameraOffset);
}

void ABow::OnAimButtonPress(float deltaTime)
{
	UPawnCameraComponent* cameraComponent = GetWeaponOwner()->GetCameraComponent();

	FRotator rotator = cameraComponent->GetComponentRotation();
	rotator.Pitch = 0;
	rotator.Roll = 0;

	GetWeaponOwner()->SetActorRotation(rotator);


	_UpdateProjectileTransform(_ProjectilesInterval);
}
void ABow::OnAimButtonUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Finished,strength: %f"), _strength));

	UPawnCameraComponent* cameraComponent = GetWeaponOwner()->GetCameraComponent();
	UCameraSpringArmComponent* CameraSpringArmComponent = GetWeaponOwner()->GetSpringArmComponent();

	_isAiming = false;
	_isDrawing = false;
	_strength = 0.0f;
	CameraSpringArmComponent->Reset();
	cameraComponent->CancelDrag();
}


void ABow::_UpdateProjectileTransform(float interval) 
{
	//get weapon,hand transform
	FTransform rightHandTransform, muzzleTransform;
	GetWeaponOwner()->GetMeshSocketTransform(EMeshSocketType::MST_RightHandDraw, ERelativeTransformSpace::RTS_World, rightHandTransform);
	muzzleTransform = GetMuzzleTransform();

	//compute Projectile Transform
	FVector dir = muzzleTransform.GetLocation() - rightHandTransform.GetLocation();

	FRotator projectileRot = dir.Rotation();


	//_arraySpawnedProjectiles.RemoveAll()
	float deltaPitch = 0;
	float deltaYaw = 0;

	for (int i = 0; i < _arraySpawnedProjectiles.Num(); ++i)
	{
		deltaPitch = (i % 2) ? interval * i  : interval * i*-1;
		FRotator rot = projectileRot;
		rot.Pitch += deltaPitch;

		if (_arraySpawnedProjectiles[i] != NULL)
		{
			_arraySpawnedProjectiles[i]->SetActorLocation(rightHandTransform.GetLocation());
			_arraySpawnedProjectiles[i]->SetActorRotation(rot);
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
			projectile->Launch(3000);
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