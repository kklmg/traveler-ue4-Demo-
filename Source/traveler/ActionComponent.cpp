// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActionComponent::MoveForward(float Value)
{
	//_pMovementHandler->SetMovementInputX(Value);
	//_pMovementHandler->SetCameraRotation(_cameraComponent->GetComponentRotation());
}

void UActionComponent::MoveRight(float Value)
{
	//_pMovementHandler->SetMovementInputY(Value);
	//_pMovementHandler->SetCameraRotation(_cameraComponent->GetComponentRotation());
}


void UActionComponent::StartJump()
{
	//bPressedJump = true;
}

void asdf() 
{
	//if (_isActive == false) return;
	//if (_movementInput.IsZero()) return;

	////translate character 
	//FRotator cameraYaw(0, _cameraRotation.Yaw, 0);
	//FVector cameraDirection(cameraYaw.Vector());
	//FVector inputDirection(_movementInput.X, _movementInput.Y, 0);

	//FMatrix inputRotaionMatrix = FRotationMatrix(inputDirection.Rotation());

	//FVector moveDirection = inputRotaionMatrix.TransformVector(cameraDirection);
	//moveDirection.Normalize();

	////character movement
	//_pCharacter->AddMovementInput(moveDirection, 100 * deltaTime);

	////let character face to moving direction
	//_pCharacter->SetActorRotation(moveDirection.Rotation());

}
