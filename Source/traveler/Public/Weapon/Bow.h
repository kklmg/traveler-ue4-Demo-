// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bow.generated.h"

class AProjectile;

/**
 * 
 */
UCLASS()
class TRAVELER_API ABow : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Fire() override;

	virtual void OnFireEnd() override;

	void AddProjectile(AProjectile* projectile);

private:
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	TArray<AProjectile*> _projectiles;
	float _strength;
	float _power;
};
