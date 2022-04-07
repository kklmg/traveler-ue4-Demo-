// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/EnumProcessState.h"
#include "Data/EnumWeaponType.h"
#include "Data/StateData.h"
#include "Interface/ExtraTransformProvider.h"
#include "WeaponBase.generated.h"

class ACreatureCharacter;
class UPoseableMeshComponent;
class UExtraTransformProviderComponent;
class UWeaponAnimationModelBase;
class UProcessManagerBase;
class IActionInterface;
class ICharacterCameraInterface;
class IProcessInterface;
class IEventBrokerInterface;

class UEventDataBase;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponSignal, AWeaponBase*, weaponIns);

namespace WeaponProcessName
{
	const FName FIRE = FName(TEXT("FIRE"));
	const FName AIM = FName(TEXT("AIM"));
}

UCLASS()
class TRAVELER_API AWeaponBase : public AActor, public IExtraTransformProvider
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void PreInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void VInitialize(ACreatureCharacter* weaponOwner);



	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void VOnEquipped();
	virtual void VOnUnEquipped();

	virtual void VReset();

	//Weapon attribute getter -----------------------------------------------------------------------------

	EAnimationState GetOwnerAnimationState();
	IActionInterface* GetOwnerActionInterface();
	ICharacterCameraInterface* GetOwnerCameraInterface();
	IEventBrokerInterface* GetEventBrokerInterface();

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMeshComponent();

	UFUNCTION(BlueprintPure)
	ACreatureCharacter* GetWeaponOwner();

	UFUNCTION(BlueprintPure)
	EWeaponType GetWeaponType();

	//Weapon Controls -----------------------------------------------------------------------------

	virtual void VWeaponControlButtonA();
	virtual void VWeaponControlButtonB();
	virtual void VWeaponControlButtonC();
	virtual void VWeaponControlButtonD();

	//Weapon process handling -----------------------------------------------------------------------------

	void ExecuteProcess(FName processName);
	void StopProcess(FName processName);
	void StopAllProcesses();
	void AddToProcessStorage(IProcessInterface* process);
	bool IsProcessRunning(FName processName);

	//MeshSocketTransform Provider Interface implementation --------------------------------------------------

	UFUNCTION(BlueprintCallable)
	virtual bool VTryGetTransform(ETransform meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform) override;

	UFUNCTION(BlueprintCallable)
	virtual bool VTryGetSocketName(ETransform transformType, FName& outSocketName) override;

	virtual void VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState);

	UFUNCTION(BlueprintPure)
	UWeaponAnimationModelBase* GetWeaponAnimationModel();

protected:
	UPROPERTY(VisibleAnywhere)
	EWeaponType _weaponType;

	EAnimationState _characterAnimationState;

private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* _skeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UExtraTransformProviderComponent* _ExtraTransformProviderComponent;

	UPROPERTY(VisibleAnywhere)
	ACreatureCharacter* _weaponOwner;

	UPROPERTY()
	UProcessManagerBase* _processManager;

	UPROPERTY()
	UWeaponAnimationModelBase* _weaponAnimationModel;

	IActionInterface* _ownerActionInterface;
	ICharacterCameraInterface* _ownerCameraInterface;
	IEventBrokerInterface* _eventBrokerInterface;

public:
	UPROPERTY(BlueprintAssignable)
	FWeaponSignal OnWeaponEquipped;
	UPROPERTY(BlueprintAssignable)
	FWeaponSignal OnWeaponUnequipped;
};