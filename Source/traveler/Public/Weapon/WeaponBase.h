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
class UProcessManagerBase;
class IActionInterface;
class ICharacterCameraInterface;
class IProcessInterface;

namespace WeaponProcessName
{
	const FName FIRE = FName(TEXT("FIRE"));
	const FName AIM = FName(TEXT("AIM"));
}

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

	EAnimationState GetOwnerAnimationState();
	IActionInterface* GetOwnerActionInterface();
	ICharacterCameraInterface* GetOwnerCameraInterface();

	virtual void VWeaponControlButtonA();
	virtual void VWeaponControlButtonB();
	virtual void VWeaponControlButtonC();
	virtual void VWeaponControlButtonD();

	virtual void VReset();

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMeshComponent();

	UFUNCTION(BlueprintPure)
	ACreatureCharacter* GetWeaponOwner();

	UFUNCTION(BlueprintPure)
	EWeaponType GetWeaponType();

	void ExecuteProcess(FName processName);
	void StopProcess(FName processName);
	void StopAllProcesses();
	void AddToProcessStorage(IProcessInterface* process);
	bool IsProcessRunning(FName processName);

	//MeshSocketTransform Provider Interface implementation --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	virtual bool VTryGetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform) override;

	UFUNCTION(BlueprintCallable)
	FName GetMeshSocketNameByType(EMeshSocketType meshSocketType);

	virtual void VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState);


protected:
	UPROPERTY(VisibleAnywhere)
	EWeaponType _weaponType;

	EAnimationState _characterAnimationState;

private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* _skeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UMeshSocketComponent* _meshSocketComponent;

	UPROPERTY(VisibleAnywhere)
	ACreatureCharacter* _weaponOwner;

	UPROPERTY()
	UProcessManagerBase* _processManager;

	IActionInterface* _ownerActionInterface;
	ICharacterCameraInterface* _ownerCameraInterface;
};