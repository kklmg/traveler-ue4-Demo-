// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeaponBase;
class ACreatureCharacter;

class IAnimationModelProvider;
class IStateInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateWeapon, AWeaponBase*,weapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EquipWeapon(AWeaponBase* weapon);

	void TakeOutWeapon(bool isTakeOut);

	void StartFiring();
	void StopFiring();

	void StartAiming();
	void StopAiming();

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon OnWeaponChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon OnWeaponFireStart;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon OnWeaponFireEnd;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon OnWeaponAimStart;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon OnWeaponAimEnd;

public:

	UPROPERTY(EditDefaultsOnly, Category = "DefaultWeapon")
	TSubclassOf<AWeaponBase> DefaultWeaponClass;

public:
	
	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetEquipedWeapon();

	UFUNCTION(BluePrintCallable)
	bool IsFiring();

	UFUNCTION(BluePrintCallable)
	bool IsAiming();

	UFUNCTION()
	void OnAnimationStateChanged(EAnimationState prevState, EAnimationState newState);
	
private:
	UPROPERTY()
	AWeaponBase* _weaponIns;

	IAnimationModelProvider* _animationModelProvider;
	IStateInterface* _stateInterface;
};
