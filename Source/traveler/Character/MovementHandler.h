// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Character.h"
/**
 * 
 */
class TRAVELER_API MovementHandler
{
public:
	MovementHandler(ACharacter *character);
	~MovementHandler();

private:
	ACharacter* const _pCharacter;

	bool _isActive;
	FVector2D _movementInput;
	FRotator _cameraRotation;

public:
	void ActivateMovement(bool isActive);

	void SetMovementInputX(float x);
	void SetMovementInputY(float y);
	void SetMovementInput(FVector2D movementInput);
	void SetCameraRotation(FRotator cameraRotation);

	void HandleMovement(float deltaTime);

private:
	

	//void OnMovementHappened();
};
