// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/MovementHandler.h"
#include "MyCharacter.generated.h"

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

	// FPS camera.
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* _cameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* _cameraSpringArm;

	UPROPERTY(EditAnywhere)
	float _zoomSpeed = 50.0f;
	

	FVector2D MovementInput;
	FVector2D CameraInput;

	MovementHandler *_pMovementHandler;
	//bool bZoomingIn;

	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomInOut(float AxisValue);
};
