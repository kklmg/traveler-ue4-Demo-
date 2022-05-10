// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Event/EventBroker.h"
#include "BowBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolChanged, bool, isTrue);

class UCommandActor;
class AArrowActorBase;
class UQuiverComponent;
class ICharacterCameraInterface;
class UCrosshairWidgetBase;

class UIntOption;
class UFloatOption;

class UBowActionFire;
class UBowActionAim;

namespace NSNameBowAnimEvent
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

	virtual bool VCanFire() override;
protected:
	virtual void PreInitializeComponents() override;

	void VInitialize(ACreatureCharacter* weaponOwner) override;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintPure)
	EBowState GetBowState();

	bool SetBowState(EBowState bowState);
	void DragCamera(bool bDrag);
	void AnimateCrosshair(bool bForward);
	bool IsDrawingBow();
	
	virtual void VOnEquipped() override;
	virtual void VOnUnEquipped() override;

	virtual void VWeaponControlA() override;
	virtual void VWeaponControlB() override;
	virtual void VWeaponControlC() override;
	virtual void VWeaponControlD() override;
	virtual void VWeaponControlE() override;
	virtual void VWeaponControlF() override;

	//animation event -------------------------------------------------------------------------

	FDelegateHandle _delegateHandle_StartDrawingBowString;
	void OnAnim_StartDrawingBowString(UObject* data);

	FDelegateHandle _delegateHandle_TakeOutArrows;
	void OnAnim_TakeOutArrows(UObject* data);

	FDelegateHandle _delegateHandle_ReleaseBowString;
	void OnAnim_ReleaseBowString(UObject* data);

	FDelegateHandle _delegateHandle_ReloadCompleted;
	void OnAnim_FullyDrawed(UObject* data);

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

private:

	// crosshair class to spawn.
	UPROPERTY(EditAnyWhere, Category = UI)
	TSubclassOf<UCrosshairWidgetBase> _crosshairWidgetClass;

	UPROPERTY()
	UCrosshairWidgetBase* _crosshairWidgetIns;

	// Projectile class to spawn.
	UPROPERTY(VisibleAnywhere, Category = Projectile)
	TArray<AArrowActorBase*> _holdingArrows;

	UPROPERTY(EditDefaultsOnly, Category = BowOptions)
	TSubclassOf<UIntOption> _arrowCountOptionClass;
	UPROPERTY()
	UIntOption* _arrowCountOptionIns;

	UPROPERTY(EditDefaultsOnly, Category = BowOptions)
	TSubclassOf<UFloatOption> _arrowIntervalOptionClass;
	UPROPERTY()
	UFloatOption* _arrowIntervalOptionIns;

	UPROPERTY(EditDefaultsOnly, Category = BowOptions)
	TSubclassOf<UFloatOption> _wristRollOptionClass;
	UPROPERTY()
	UFloatOption* _wristRollOptionIns;

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
	UBowActionFire* _processFire;

	UPROPERTY()
	UBowActionAim* _processAim;

	float _strength;
};
