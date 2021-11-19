// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolChanged, bool, isTrue);

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

	virtual void OnFireButtonDown() override;
	virtual void OnFireButtonPress(float deltaTime) override;
	virtual void OnFireButtonUp() override;

	virtual void OnAimButtonDown() override;
	virtual void OnAimButtonPress(float deltaTime) override;
	virtual void OnAimButtonUp() override;

	virtual void OnEnterAnimFrame_ReloadStart() override;
	virtual void OnTickAnimFrame_Reloading() override;
	virtual void OnEnterAnimFrame_ReloadCompleted() override;

	virtual FTransform GetMuzzleTransform() override;

	UFUNCTION(BlueprintCallable)
	void OnEnterAnimFrame_StartDrawingBow();

	UFUNCTION(BlueprintCallable)
	void OnEnterAnimFrame_GrabArrow();

	UFUNCTION(BlueprintCallable)
	virtual void OnEnterAnimFrame_Launch() override;
	
	void AddProjectile(AProjectile* projectile);

	UFUNCTION(BlueprintCallable)
	bool isDrawing();
	//FOnBoolChanged DrawingStateChanged;

private:
	float _CalculateDamage();
	float _CalculateProjectileSpeed();

	void _SpawnProjectile(int count);

	void _UpdateProjectileTransform(float interval);

private:

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = ProjectileClass)
	TSubclassOf<class AProjectile> ProjectileClass;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TArray<AProjectile*> _arraySpawnedProjectiles;

	UPROPERTY(EditAnyWhere, Category = Attribute, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float _drawingVelocity;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _spawnProjectileCount;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _ProjectilesInterval;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _maxDamage;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _baseProjectileVelocity;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _maxProjectileVelocity;

	UPROPERTY(EditAnyWhere, Category = Camera)
	FVector _aimingCameraOffset;

	UPROPERTY(EditDefaultsOnly, Category = MeshSocket)
	FName _meshSocketMuzzle;


	bool _isAiming;
	bool _isDrawing;

	float _strength;

	TArray<AProjectile*> _projectiles;
};
