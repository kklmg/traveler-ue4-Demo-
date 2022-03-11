// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/MyGameplayStatics.h"
#include "Camera/CameraComponent.h"

FVector UMyGameplayStatics::InptAxisToCameraDirection(FVector inputAxis, UCameraComponent* cameraComp)
{
	//Get Camera Rotation Matrix
	FRotator cameraRotator = cameraComp->GetComponentRotation();


	FVector moveDirection = cameraRotator.RotateVector(inputAxis);
	moveDirection.Z = 0;
	moveDirection.Normalize();

	return moveDirection;
}

float UMyGameplayStatics::ComputeDistance(FVector from, FVector to, EPlane plane /*= Plane_None*/)
{
	FVector dirFromTo = to - from;

	switch (plane)
	{
		case Plane_None:
		{
			return dirFromTo.Size();
		}
		break;
		case Plane_XY:
		{
			dirFromTo.Z = 0;
			dirFromTo.Size();
		}
		break;
		case Plane_XZ: 
		{
			dirFromTo.Y = 0;
			dirFromTo.Size();
		}
			break;
		case Plane_YZ: 
		{
			dirFromTo.X = 0;
			dirFromTo.Size();
		}
		break;
	}
	
	return dirFromTo.Size();
}

