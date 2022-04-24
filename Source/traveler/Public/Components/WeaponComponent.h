// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


class UAnimationModelBase;

class AWeaponBase;
class ACreatureCharacter;

class UProcessBase;
class ULifeControlComponent;
class UExTransformProviderComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateWeapon, AWeaponBase*,weapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	void BindInputs(UInputComponent* PlayerInputComponent);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	void OnLifeChanged(bool isAlive);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UProcessBase* GetWeaponProcess(FName processName);
	void ExecuteWeaponProcess(FName processName);
	void TickWeaponProcess(FName processName,float deltaTime);
	void StopWeaponProcess(FName processName);
	void StopAllWeaponProcesses();

	void EquipWeapon(AWeaponBase* weapon);

	void TakeOutWeapon(bool isTakeOut);

	void WeaponControlButtonA();
	void WeaponControlButtonB();
	void WeaponControlButtonC();
	void WeaponControlButtonD();
public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon OnWeaponChanged;

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

	UPROPERTY()
	UAnimationModelBase* _animationViewModel;

	UPROPERTY()
	ULifeControlComponent* _lifeControlComp;

	UPROPERTY()
	UExTransformProviderComponent* _ownerExTransformProviderComp;
};
