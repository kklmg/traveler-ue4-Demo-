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
	ABow();
public:
	void Tick(float DeltaTime) override;

	virtual void OnFireStart() override;
	virtual void FiringInProgress(float deltaTime) override;
	virtual void OnFireEnd() override;

	virtual void OnAimStart() override;
	virtual void AimmingInProgress(float deltaTime) override;
	virtual void OnAimEnd() override;

	virtual void OnEnterAnimFrame_ReloadStart() override;
	virtual void OnTickAnimFrame_Reloading() override;
	virtual void OnEnterAnimFrame_ReloadCompleted() override;

	virtual void OnEnterAnimFrame_Launch() override;
	
	void AddProjectile(AProjectile* projectile);

	void DrawBowString();

	void ResetBowString();

private:
	float _CalculateDamage();
	float _CalculateProjectileSpeed();
	void _SpawnProjectile();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Bone")
	FName _bonePullTop;

	UPROPERTY(EditDefaultsOnly, Category = "Bone")
	FName _bonePullBottom;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnyWhere, Category = Attribute, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float _drawingVelocity;

	UPROPERTY(EditAnyWhere, Category = Attribute)
	float _maxDamage;

	UPROPERTY(EditAnyWhere, Category = Attribute)
	float _baseProjectileVelocity;

	UPROPERTY(EditAnyWhere, Category = Attribute)
	float _maxProjectileVelocity;

	UPROPERTY(EditAnyWhere, Category = Camera)
	FVector _aimingCameraOffset;

	UPROPERTY(EditAnyWhere, Category = Animation)
	UAnimMontage* _fireAnimMontage;

	bool _isAiming;
	float _strength;

	TArray<AProjectile*> _projectiles;
};
