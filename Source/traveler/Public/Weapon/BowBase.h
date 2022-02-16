// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Data/BowAnimationModelBase.h"
#include "BowBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolChanged, bool, isTrue);

class UCommandActor;
class AArrowActorBase;

class UQuiverComponent;

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

	UFUNCTION(BlueprintCallable)
	FBowAnimationModelBase GetAnimationModel();

	UFUNCTION(BlueprintCallable)
	void OnEnterAnimFrame_StartDrawingBowString();
	UFUNCTION(BlueprintCallable)
	void OnEnterAnimFrame_TakeOutArrows();
	UFUNCTION(BlueprintCallable)
	virtual void OnEnterAnimFrame_ReleaseBowString();
	UFUNCTION(BlueprintCallable)
	void OnEnterAnimFrame_ReloadCompleted();

	UFUNCTION(BlueprintPure)
	EBowState GetBowState();

	virtual void VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState) override;

	virtual void VWeaponControlButtonA() override;
	virtual void VWeaponControlButtonB() override;

	virtual void VWeaponControlAxisA(float value) override;
	virtual void VWeaponControlAxisB(float value) override;

protected:
	void TakeOutArrows();
	void ClearHoldingArrows();
	void LaunchArrows();

	void AdjustHandRotation(float value);
	void AdjustArrowIntervals(float value);

	void IncreaseArrows();
	void DecreaseArrows();

protected:
	virtual bool VTMCanFire() override;
	virtual bool VTMCanAim() override;

	virtual void VTMStartFiring() override;
	virtual void VTMFiringInProgress(float deltaTime) override;
	virtual void VTMStopFiring() override;

	virtual void VTMStarAiming() override;
	virtual void VTMAimingInProgress(float deltaTime) override;
	virtual void VTMStopAiming() override;

	virtual void VReset() override;

private:
	float _CalculateDamage();
	float _CalculateProjectileSpeed();

	void UpdateArrowsTransform();
	void AttachArrowsToHand();
	void AttachArrowsToBow();

private:

	// Projectile class to spawn.
	UPROPERTY(VisibleAnywhere, Category = Projectile)
	TArray<AArrowActorBase*> _holdingArrows;

	UPROPERTY(EditAnyWhere, Category = Attribute, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float _drawingVelocity;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _holdCountOnceMin;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _holdCountOnceMax;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _holdCountOnce;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _holdCountStep;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _arrowsIntervalMin;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _arrowsIntervalMax;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _arrowsInterval;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _arrowsIntervalStep;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _handRollMin;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _handRollMax;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _handRoll;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _handRollStep;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _maxDamage;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _baseProjectileVelocity;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	float _maxProjectileVelocity;

	UPROPERTY(EditAnyWhere, Category = Camera)
	FVector _aimingCameraOffset;
	
	UPROPERTY(EditDefaultsOnly, Category = bowState)
	EBowState _bowState;

	float _strength;

	UPROPERTY(VisibleAnywhere, Category = AnimationModel)
	FBowAnimationModelBase _animationModel;

	ICharacterCameraInterface* _characterCamera;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UQuiverComponent* _quiverComponent;
};
