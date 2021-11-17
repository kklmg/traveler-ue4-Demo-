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
}

void ABow::OnFireStart()
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

void ABow::FiringInProgress(float deltaTime)
{
	//UGameplayStatics::PredictProjectilePath();

	//FiringInProgress();


}

void ABow::OnFireEnd() 
{
	//_SpawnProjectile();

	//if (_fireAnimMontage != nullptr)
	//{
	//	//_fireAnimMontage->noti
	//	//GetWeaponOwner()->PlayAnimMontage(_fireAnimMontage, 1.0f, TEXT("Release"));
	//}
}

void ABow::OnAimStart()
{
	_isAiming = true;

	UCameraSpringArmComponent* CameraSpringArmComponent = GetWeaponOwner()->GetSpringArmComponent();
	UPawnCameraComponent* cameraComponent = GetWeaponOwner()->GetCameraComponent();

	CameraSpringArmComponent->SetPitchRange(-60, 60);
	cameraComponent->BeginDragCamera(_aimingCameraOffset);
	
}
void ABow::AimmingInProgress(float deltaTime)
{
	UPawnCameraComponent* cameraComponent = GetWeaponOwner()->GetCameraComponent();

	FRotator rotator = cameraComponent->GetComponentRotation();
	rotator.Pitch = 0;
	rotator.Roll = 0;

	GetWeaponOwner()->SetActorRotation(rotator);



	FTransform rightHandTransform, weaponTransform;
	GetWeaponOwner()->GetMeshSocketTransform(EMeshSocketType::MST_RightHandDraw,ERelativeTransformSpace::RTS_World, rightHandTransform);
	weaponTransform = this->GetTransform();


	FVector dir = weaponTransform.GetLocation() - rightHandTransform.GetLocation();
	FRotator projectileRot = dir.Rotation();
	projectileRot.Pitch += 20;

	for(AProjectile* projectile : _arraySpawnedProjectiles)
	{
		if (projectile != NULL)
		{
			projectile->SetActorLocation(rightHandTransform.GetLocation());
			projectile->SetActorRotation(projectileRot);
			projectileRot.Pitch -= 10;
		}
	}
}
void ABow::OnAimEnd()
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
	//_SpawnProjectile();
	_isDrawing = false;
}

void ABow::OnEnterAnimFrame_StartDrawingBow()
{
	_isDrawing = true;
}

void ABow::OnEnterAnimFrame_GrabArrow() 
{
	_SpawnProjectile();
	_SpawnProjectile();
	_SpawnProjectile();
	_SpawnProjectile();
	_SpawnProjectile();
}


void ABow::AddProjectile(AProjectile* projectile) 
{
	_projectiles.Add(projectile);
}

void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isAiming)
	{
		_strength = FMath::Clamp(_strength + DeltaTime * _drawingVelocity, 0.0f, 1.0f);
	}
}
void ABow::_SpawnProjectile()
{
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		UPawnCameraComponent* cameraComponent = GetWeaponOwner()->GetCameraComponent();

		// Get actor location
		FVector weaponLocation = GetActorLocation();

		//Get Camera Rotation Rotator
		FRotator cameraRotator = cameraComponent->GetComponentRotation();

		//calculate muzzle position
		FVector MuzzleOffset;
		MuzzleOffset.Set(50.0f, 0.0f, 0.0f);

		FVector MuzzleLocation = weaponLocation + FTransform(cameraRotator).TransformVector(MuzzleOffset);
		

		FHitResult hitResult;
		FVector cameraforwardVector = cameraComponent->GetForwardVector();
		FVector farPlaneCenter = cameraforwardVector * cameraComponent->OrthoFarClipPlane;
		FCollisionQueryParams CollisionParams;

		FVector hitLocation = farPlaneCenter;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, cameraComponent->GetComponentLocation(), farPlaneCenter, ECC_Visibility, CollisionParams))
		{
			if (hitResult.bBlockingHit)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *hitResult.GetActor()->GetName()));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Impact Point: %s"), *hitResult.ImpactPoint.ToString()));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Normal Point: %s"), *hitResult.ImpactNormal.ToString()));
			}
			hitLocation = hitResult.ImpactPoint;
		}


			//UObject * WorldContextObject, 
			//FPredictProjectilePathParams PredictParams;
			//FPredictProjectilePathResult  PredictResult;


			//UGameplayStatics::PredictProjectilePath(GetWorld(), PredictParams, PredictResult);
		

		
		FVector projectileDirection = hitLocation - MuzzleLocation;
		projectileDirection.Normalize();
		FRotator MuzzleRotation = projectileDirection.Rotation();

		//DrawDebugLine(GetWorld(), MuzzleLocation, hitLocation, FColor::Blue, false, 2.0f);

		//Spawn Projectile
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetWeaponOwner();

			// Spawn the projectile at the muzzle.
			//AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			/*if (Projectile)
			{
				Projectile->Initialize(_CalculateDamage(), _CalculateProjectileSpeed());
				Projectile->FireInDirection(projectileDirection);
			}*/

			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass);
			//Projectile->AttachToComponent(GetMeshComponent(), FAttachmentTransformRules::KeepRelativeTransform, _meshSocketBowStringCenter);

			_arraySpawnedProjectiles.Add(Projectile);
			//Projectile->AttachToComponent(GetWeaponOwner()->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, GetWeaponOwner()->GetMeshSocketNameByType(EMeshSocketType::MST_RightHandDraw));
			
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