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

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon onWeaponChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon onWeaponFireStart;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon onWeaponFireEnd;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon onWeaponAimStart;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon onWeaponAimEnd;


	UPROPERTY(EditDefaultsOnly, Category = "DefaultWeapon")
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName SocketLeftHand;

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
