// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UPawnCameraComponent;
class UCameraSpringArmComponent;
class UStateComponent;
class MovementHandler;
class UActionComponent;
class UWeaponComponent;
class UAttributeComponent;

class AProjectile;


UCLASS()
class TRAVELER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

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
	UStateComponent* GetStateComponent();

	UFUNCTION(BlueprintCallable)
	UCameraSpringArmComponent* GetSpringArmComponent();

	UFUNCTION(BlueprintCallable)
	UPawnCameraComponent* GetCameraComponent();

	UFUNCTION(BlueprintCallable)
	UAttributeComponent* GetAttributeComponent();

	UFUNCTION(BlueprintCallable)
	UWeaponComponent* GetWeaponComponent();

	UFUNCTION(BlueprintCallable)
	void LaunchProjectile();

	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
	void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
	void StopJump();

	// Function that handles firing projectiles.
	//UFUNCTION()
	//void Aim();

	// Function that handles firing projectiles.
	//UFUNCTION()
	//void CancelAim();

private:
	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, Category = Gameplay)
	FVector MuzzleOffset;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	// FPS camera.
	UPROPERTY(VisibleAnywhere)
	UPawnCameraComponent* _cameraComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraSpringArmComponent* _cameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UStateComponent* _stateComponent;

	UPROPERTY(VisibleAnywhere)
	UActionComponent* _actionComponent;

	UPROPERTY(VisibleAnywhere)
	UWeaponComponent* _weaponComponent;

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* _attributeComponent;

	FVector2D MovementInput;
	FVector2D CameraInput;

	MovementHandler* _pMovementHandler;
};
