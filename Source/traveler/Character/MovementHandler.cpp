// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementHandler.h"
#include "GameFramework/Character.h"

MovementHandler::MovementHandler(ACharacter* character) : _pCharacter(character), _isActive(true)
{
}

MovementHandler::~MovementHandler()
{
}

void MovementHandler::ActivateMovement(bool isActive) 
{
	_isActive = isActive;
}

void MovementHandler::SetMovementInputX(float x) 
{
	_movementInput.X = x;
}
void MovementHandler::SetMovementInputY(float y)
{
	_movementInput.Y = y;
}

void MovementHandler::SetMovementInput(FVector2D movementInput)
{
	_movementInput = movementInput;
}

void MovementHandler::SetCameraRotation(FRotator cameraRotation)
{
	_cameraRotation = cameraRotation;
}

void MovementHandler::HandleMovement(float deltaTime)
{
	if (_isActive == false) return;
	if (_movementInput.IsZero()) return;

	//translate character 
	FRotator cameraYaw(0, _cameraRotation.Yaw, 0);
	FVector cameraDirection(cameraYaw.Vector());
	FVector inputDirection(_movementInput.X, _movementInput.Y, 0);

	FMatrix inputRotaionMatrix = FRotationMatrix(inputDirection.Rotation());
	
	FVector moveDirection = inputRotaionMatrix.TransformVector(cameraDirection);
	moveDirection.Normalize();

	//character movement
	_pCharacter->AddMovementInput(moveDirection, 50 * deltaTime);

	//let character face to moving direction
	_pCharacter->SetActorRotation(moveDirection.Rotation());
}
