// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/EnumWeaponType.h"
#include "WeaponBase.generated.h"

class ACreatureCharacter;
class UPoseableMeshComponent;
class UWeaponAnimationModelBase;


UCLASS()
class TRAVELER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void VInitialize(ACreatureCharacter* weaponOwner);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* _skeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	ACreatureCharacter* _weaponOwner;

	bool _isReadyToFire;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	EWeaponType WeaponType;

public:
	void StartFiring();
	void FiringInProgress(float deltaTime);
	void StopFiring();
	bool IsFiring();

	void StarAiming();
	void AimingInProgress(float deltaTime);
	void StopAiming();
	bool IsAiming();

	void StopAllActions();

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMeshComponent();

	UFUNCTION(BlueprintCallable)
	ACreatureCharacter* GetWeaponOwner();

	//UFUNCTION(BlueprintCallable)
	//UWeaponAnimationModelBase* GetAnimationModel();

protected:
	virtual bool VTMCanFire() PURE_VIRTUAL(AWeaponBase::VTMCanFire, return false;);
	virtual bool VTMCanAim() PURE_VIRTUAL(AWeaponBase::VTMCanAim, return false;);

	virtual void VTMStartFiring() PURE_VIRTUAL(AWeaponBase::VTMStartFiring, );
	virtual void VTMFiringInProgress(float deltaTime) PURE_VIRTUAL(AWeaponBase::VTMFiringInProgress, );
	virtual void VTMStopFiring()PURE_VIRTUAL(AWeaponBase::VTMStopFiring, );

	virtual void VTMStarAiming()PURE_VIRTUAL(AWeaponBase::VTMStarAiming, );
	virtual void VTMAimingInProgress(float deltaTime)PURE_VIRTUAL(AWeaponBase::VTMAimingInProgress, );
	virtual void VTMStopAiming()PURE_VIRTUAL(AWeaponBase::VTMStopAiming, );

	//UPROPERTY()
	//UWeaponAnimationModelBase* _animationModel;
private:
	bool _isFiring;
	bool _isAiming;

	
};