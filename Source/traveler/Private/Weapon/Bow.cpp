// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bow.h"
#include "Projectile/Projectile.h"
#include "Character/MyCharacter.h"
#include "Camera/CameraComponent.h"

void ABow::Fire() 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Trigger Fire");
}

void ABow::OnFireEnd() 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Fire Finished");

	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		UCameraComponent* cameraComponent = _owner->GetCameraComponent();

		// Get actor location
		FVector actorLocation = _owner->GetActorLocation();

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
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}


void ABow::AddProjectile(AProjectile* projectile) 
{
	_projectiles.Add(projectile);
}