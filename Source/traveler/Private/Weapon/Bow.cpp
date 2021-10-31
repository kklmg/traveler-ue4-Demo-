// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bow.h"
#include "Projectile/Projectile.h"
#include "Character/MyCharacter.h"
#include "Components/PawnCameraComponent.h"

ABow::ABow() 
{
	_isDrawing = false;
	_strength = 0.0f;
	_maxDamage = 0.0f;
	_drawingVelocity = 0.5f;
	_maxProjectileVelocity = 2000.0f;
}

void ABow::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Trigger Fire");

	_isDrawing = true;

	UPawnCameraComponent* cameraComponent = _owner->GetCameraComponent();
	cameraComponent->BeginDragCamera(FVector(20,20,20));
}

void ABow::OnFireEnd() 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Finished,strength: %f"), _strength));
	
	_SpawnProjectile();

	_isDrawing = false;
	_strength = 0.0f;

	UPawnCameraComponent* cameraComponent = _owner->GetCameraComponent();
	cameraComponent->CancelDrag();
}


void ABow::AddProjectile(AProjectile* projectile) 
{
	_projectiles.Add(projectile);
}

void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isDrawing)
	{
		_strength = FMath::Clamp(_strength + DeltaTime * _drawingVelocity, 0.0f, 1.0f);
	}


}
void ABow::_SpawnProjectile()
{
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		UPawnCameraComponent* cameraComponent = _owner->GetCameraComponent();

		// Get actor location
		FVector actorLocation = _owner->GetPawnViewLocation();

		//Get Camera Rotation Matrix
		FRotator cameraRotator = cameraComponent->GetComponentRotation();
		FMatrix cameraRotationMatrix = FRotationMatrix(cameraRotator);

		//calculate muzzle position
		FVector MuzzleOffset;
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		FVector MuzzleLocation = actorLocation + FTransform(cameraRotator).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = cameraRotator;

		//Spawn Projectile
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				Projectile->Initialize(_CalculateDamage(), _CalculateProjectileSpeed());
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}


float ABow::_CalculateDamage() 
{
	return _strength * _maxDamage;
}

float ABow::_CalculateProjectileSpeed()
{
	return _strength * _maxProjectileVelocity;
}