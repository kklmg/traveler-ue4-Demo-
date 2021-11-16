// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateWeapon, AWeapon*,weapon);

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetWeapon(AWeapon* weapon);

	void SetWhetherEquipWeapon(bool isEquiped);

	void OnFireButtonDown();
	void OnFireButtonUp();

	void OnAimButtonDown();
	void OnAimButtonUp();

	UFUNCTION(BlueprintCallable, Category = "OnAnimationFrameStart")
	void OnAnimFrameStart_Fire();

	UFUNCTION(BlueprintCallable, Category = "OnAnimationFrameStart")
	void OnAnimFrameStart_FireReady();

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
	TSubclassOf<AWeapon> DefaultWeaponClass;

public:
	
	UFUNCTION(BlueprintCallable)
	AWeapon* GetEquipedWeapon();

	UFUNCTION(BluePrintCallable)
	bool IsFiring();

	UFUNCTION(BluePrintCallable)
	bool IsAiming();

private:
	AWeapon* _aWeapon;

	bool _isFiring;
	bool _isAiming;
};
