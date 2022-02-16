// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/EnumWeaponType.h"
#include "Data/StateData.h"
#include "Interface/MeshSocketTransformProvider.h"
#include "WeaponBase.generated.h"

class ACreatureCharacter;

class UPoseableMeshComponent;
class UMeshSocketComponent;

class UWeaponAnimationModelBase;


UCLASS()
class TRAVELER_API AWeaponBase : public AActor, public IMeshSocketTransformProvider
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

	//MeshSocketTransform Provider Interface implementation --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	virtual bool VTryGetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform) override;

	UFUNCTION(BlueprintCallable)
	FName GetMeshSocketNameByType(EMeshSocketType meshSocketType);

	virtual void VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState);

private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* _skeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UMeshSocketComponent* _meshSocketComponent;

	UPROPERTY(VisibleAnywhere)
	ACreatureCharacter* _weaponOwner;

	bool _isReadyToFire;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	EWeaponType WeaponType;

public:

//Controls
	void StartFiring();
	void FiringInProgress(float deltaTime);
	void StopFiring();
	bool IsFiring();

	void StarAiming();
	void AimingInProgress(float deltaTime);
	void StopAiming();
	bool IsAiming();

	virtual void VWeaponControlButtonA();
	virtual void VWeaponControlButtonB();
	virtual void VWeaponControlButtonC();
	virtual void VWeaponControlButtonD();

	void StopAllActions();
	virtual void VReset();

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
protected:
	bool _isFiring;
	bool _isAiming;
	EAnimationState _characterAnimationState;
};