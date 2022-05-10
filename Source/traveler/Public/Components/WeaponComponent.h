// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class UAnimationModelBase;
class UProcessBase;
class UEventBrokerComponent;
class UExTransformProviderComponent;
class UAnimControlComponent;
class UActionComponent;
class AWeaponBase;
class ACreatureCharacter;

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

	void WeaponControlA();
	void WeaponControlB();
	void WeaponControlC();
	void WeaponControlD();
	void WeaponControlE();
	void WeaponControlF();
public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDelegateWeapon OnWeaponChanged;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultWeapon")
	TSubclassOf<AWeaponBase> DefaultWeaponClass;

public:
	
	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetEquipedWeapon();
	
private:
	UPROPERTY()
	AWeaponBase* _weaponIns;

	UPROPERTY()
	UActionComponent* _actionComp;

	UPROPERTY()
	UAnimControlComponent* _animControlComp;

	UPROPERTY()
	UExTransformProviderComponent* _ownerExTransformProviderComp;
};
