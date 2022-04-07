// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Event/EventDataBase.h"
#include "BowBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolChanged, bool, isTrue);

class UCommandActor;
class AArrowActorBase;
class UQuiverComponent;
class ICharacterCameraInterface;
class UCrosshairWidgetBase;

class UBowProcessFire;
class UBowProcessAim;

namespace BowAnimEventName
{
	const FName Bow_FullyDrawed = FName(TEXT("Anim_Bow_FullyDrawed"));
	const FName Bow_DrawingBowString = FName(TEXT("Anim_Bow_DrawingBowString"));
	const FName Bow_TakeOutArrows = FName(TEXT("Anim_Bow_TakeOutArrows"));
	const FName Bow_ReleasedBowString = FName(TEXT("Anim_Bow_ReleasedBowString"));
};

/**
 * 
 */
UCLASS()
class TRAVELER_API ABowBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	ABowBase(const FObjectInitializer& ObjectInitializer);
public:
	void VInitialize(ACreatureCharacter* weaponOwner) override;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	EBowState GetBowState();

	bool SetBowState(EBowState bowState);
	void DragCamera(bool bDrag);
	void AnimateCrosshair(bool bForward);
	void SetStrength(float elapsedTime);
	bool IsDrawingBow();
	
	virtual void VOnEquipped() override;
	virtual void VOnUnEquipped() override;

	virtual void VWeaponControlButtonA() override;
	virtual void VWeaponControlButtonB() override;
	virtual void VWeaponControlButtonC() override;
	virtual void VWeaponControlButtonD() override;

	//animation event -------------------------------------------------------------------------

	virtual void VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState) override;

	FDelegateHandle _delegateHandle_StartDrawingBowString;
	void OnAnim_StartDrawingBowString(UEventDataBase* eventData);

	FDelegateHandle _delegateHandle_TakeOutArrows;
	void OnAnim_TakeOutArrows(UEventDataBase* eventData);

	FDelegateHandle _delegateHandle_ReleaseBowString;
	void OnAnim_ReleaseBowString(UEventDataBase* eventData);

	FDelegateHandle _delegateHandle_ReloadCompleted;
	void OnAnim_FullyDrawed(UEventDataBase* eventData);

protected:
	void TakeOutArrows();
	void ClearHoldingArrows(bool bDeactivateArrows);
	void LaunchArrows();

	void AdjustHandRotation();
	void AdjustArrowIntervals();
	void IncreaseArrows();
	void DecreaseArrows();

protected:
	virtual void VReset() override;

private:

	float CalculateDamage();
	float CalculateProjectileSpeed();

	void UpdateArrowsTransform();
	void AttachArrowsToHand();
	void AttachArrowsToBow();

	void OnFireProcessChanged(EProcessState processState);
	void OnAimProcessChanged(EProcessState processState);

private:

	// crosshair class to spawn.
	UPROPERTY(EditAnyWhere, Category = UI)
	TSubclassOf<UCrosshairWidgetBase> _crosshairWidgetClass;

	UPROPERTY()
	UCrosshairWidgetBase* _crosshairWidgetIns;

	// Projectile class to spawn.
	UPROPERTY(VisibleAnywhere, Category = Projectile)
	TArray<AArrowActorBase*> _holdingArrows;

	UPROPERTY(EditAnyWhere, Category = Attribute, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float _drawingVelocity;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	TArray<float> _arrowSpawnCountArray;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	int32  _arrowSpawnCountSelectID;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	TArray<float> _arrowIntervalArray;
	UPROPERTY(EditAnyWhere, Category = Projectile)
	int32 _arrowIntervalSelectID;

	UPROPERTY(EditAnyWhere, Category = Projectile)
	TArray<float> _handRollArray;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	int32 _handRollSelectID;

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

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UQuiverComponent* _quiverComponent;

	UPROPERTY()
	TArray<FDelegateHandleData> _delegateHandles;

	UPROPERTY()
	UBowProcessFire* _processFire;

	UPROPERTY()
	UBowProcessAim* _processAim;

	float _strength;
};
