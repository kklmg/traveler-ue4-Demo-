// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "BowBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolChanged, bool, isTrue);

class AProjectile;
class UCommandActor;

class ICharacterCameraInterface;

/**
 * 
 */
UCLASS()
class TRAVELER_API ABowBase : public AWeaponBase
{
	GENERATED_BODY()
public:
	ABowBase();
public:
	void VInitialize(ACreatureCharacter* weaponOwner) override;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	virtual bool VTMCanFire() override;
	virtual bool VTMCanAim() override;

	virtual void VTMStartFiring() override;
	virtual void VTMFiringInProgress(float deltaTime) override;
	virtual void VTMStopFiring() override;

	virtual void VTMStarAiming() override;
	virtual void VTMAimingInProgress(float deltaTime) override;
	virtual void VTMStopAiming() override;

	virtual FTransform GetMuzzleTransform();

	UFUNCTION(BlueprintCallable)
	void OnEnterAnimFrame_StartDrawingBow();

	UFUNCTION(BlueprintCallable)
	void OnEnterAnimFrame_GrabArrow();

	UFUNCTION(BlueprintCallable)
	virtual void OnEnterAnimFrame_Launch();
	
	void AddProjectile(AProjectile* projectile);

	UFUNCTION(BlueprintCallable)
	bool isDrawing();
	//FOnBoolChanged DrawingStateChanged;

private:
	float _CalculateDamage();
	float _CalculateProjectileSpeed();

	void _SpawnProjectiles(int count);

	void _UpdateProjectileTransform(float deltaDegree);

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



	bool _isDrawing;

	float _strength;

	TArray<AProjectile*> _projectiles;

	UPROPERTY(EditDefaultsOnly, Category = Button)
	TSubclassOf<UCommandActor> _aimButtonCommandClass;

	UPROPERTY()
	UCommandActor* _aimButtonCommand;

	ICharacterCameraInterface* _characterCamera;
};
