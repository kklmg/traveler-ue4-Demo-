// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/EnumProcessState.h"
#include "Enums/EnumWeaponType.h"
#include "MyMacros.h"
#include "WeaponBase.generated.h"

class ACreatureCharacter;
class UProcessBase;
class UPoseableMeshComponent;
class UExTransformProviderComponent;
class UActionComponent;
class UEventBrokerComponent;

class UWeaponAnimationModelBase;
class UProcessManagerBase;
class ICharacterCameraInterface;
class UActionPresetGroup;
class UEventDataBase;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponSignal, AWeaponBase*, weaponIns);

namespace NSNameWeaponActionProcess
{
	DECLARE_CONST_FNAME(FIRE)
	DECLARE_CONST_FNAME(AIM)
}

UCLASS()
class TRAVELER_API AWeaponBase : public AActor
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
	virtual void OnWeaponCompTick(float deltaTime);

	virtual bool VCanFire();
	virtual void VOnEquipped();
	virtual void VOnUnEquipped();

	TSubclassOf<UActionPresetGroup> GetActionPresetGroupClass();

	virtual void VReset();

	//Weapon attribute getter -----------------------------------------------------------------------------
	UFUNCTION(BlueprintPure)
	UExTransformProviderComponent* GetExTransformProviderComp();
	UFUNCTION(BlueprintPure)
	UExTransformProviderComponent* GetOwnerExTransformProviderComp();
	UFUNCTION(BlueprintPure)
	UEventBrokerComponent* GetOwnerEventBrokerComp();
	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMeshComponent();
	UFUNCTION(BlueprintPure)
	ACreatureCharacter* GetWeaponOwner();
	UFUNCTION(BlueprintPure)
	EWeaponType GetWeaponType();

	ICharacterCameraInterface* GetOwnerCameraInterface();

	//Weapon Controls -----------------------------------------------------------------------------

	virtual void VWeaponControlA();
	virtual void VWeaponControlB();
	virtual void VWeaponControlC();
	virtual void VWeaponControlD();
	virtual void VWeaponControlE();
	virtual void VWeaponControlF();

	//Weapon process handling -----------------------------------------------------------------------------


	UFUNCTION(BlueprintPure)
	UWeaponAnimationModelBase* GetWeaponAnimationModel();

protected:
	UPROPERTY(VisibleAnywhere)
	EWeaponType _weaponType;

private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* _skeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UExTransformProviderComponent* _extraTransformProviderComp;

	UPROPERTY(VisibleAnywhere)
	UExTransformProviderComponent* _ownerExtraTransformProviderComp;

	UPROPERTY(VisibleAnywhere)
	ACreatureCharacter* _weaponOwner;

	UPROPERTY()
	UWeaponAnimationModelBase* _weaponAnimationModel;

	UPROPERTY()
	UEventBrokerComponent* _ownerEventBrokerComp;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UActionPresetGroup> _actionPresetGroupClass;

	ICharacterCameraInterface* _ownerCameraInterface;

public:
	UPROPERTY(BlueprintAssignable)
	FWeaponSignal OnWeaponEquipped;
	UPROPERTY(BlueprintAssignable)
	FWeaponSignal OnWeaponUnequipped;
};