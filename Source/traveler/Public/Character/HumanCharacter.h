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

DECLARE_DELEGATE(FButtonSignature);


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

	UFUNCTION()
	void OnAction1ButtonDown();
	UFUNCTION()
	void OnAction1ButtonUp();
	UFUNCTION()
	void OnAction2ButtonDown();
	UFUNCTION()
	void OnAction2ButtonUp();
	UFUNCTION()
	void OnAction3ButtonDown();
	UFUNCTION()
	void OnAction3ButtonUp();

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

	//delegates
public:
	FButtonSignature Action1ButtonDownDelegate;
	FButtonSignature Action1ButtonUpDelegate;

	FButtonSignature Action2ButtonDownDelegate;
	FButtonSignature Action2ButtonUpDelegate;

	FButtonSignature Action3ButtonDownDelegate;
	FButtonSignature Action3ButtonUpDelegate;
};
