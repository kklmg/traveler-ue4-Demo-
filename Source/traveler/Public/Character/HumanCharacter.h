// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CreatureCharacter.h"
#include "HumanCharacter.generated.h"

class UPawnCameraComponent;
class UCameraSpringArmComponent;
class UWeaponComponent;

class AWeapon;
class AProjectile;


UCLASS()
class TRAVELER_API AHumanCharacter : public ACreatureCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHumanCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	UCameraSpringArmComponent* GetSpringArmComponent();

	UFUNCTION(BlueprintCallable)
	UPawnCameraComponent* GetCameraComponent();

	UFUNCTION(BlueprintCallable)
	UWeaponComponent* GetWeaponComponent();

	UFUNCTION(BlueprintCallable)
	AWeapon* GetEquippedWeapon();

private:
	// FPS camera.
	UPROPERTY(VisibleAnywhere)
	UPawnCameraComponent* _cameraComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraSpringArmComponent* _cameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UWeaponComponent* _weaponComponent;
};
