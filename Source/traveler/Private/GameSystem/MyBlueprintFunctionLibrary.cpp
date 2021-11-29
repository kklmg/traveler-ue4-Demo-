// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/MyBlueprintFunctionLibrary.h"
#include "Camera/CameraComponent.h"

FVector UMyBlueprintFunctionLibrary::InptAxisToCameraDirection(FVector inputAxis, UCameraComponent* cameraComp)
{
	//Get Camera Rotation Matrix
	FRotator cameraRotator = cameraComp->GetComponentRotation();

	FVector moveDirection = cameraRotator.RotateVector(inputAxis);
	moveDirection.Z = 0;
	moveDirection.Normalize();

	return moveDirection;
}