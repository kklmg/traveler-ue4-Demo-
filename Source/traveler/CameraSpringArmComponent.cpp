// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSpringArmComponent.h"

UCameraSpringArmComponent::UCameraSpringArmComponent() 
{
	SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	TargetArmLength = 250.0f;
	bEnableCameraLag = false;
	//CameraLagSpeed = 3.0f;

	//zoom 
	_zoomMax = 400;
	_zoomMin = 100; 
	_zoomFactor = 20;
}

void UCameraSpringArmComponent::Pitch(float AxisValue) 
{
	FRotator rotation = GetRelativeRotation();
	float pitch = rotation.Pitch + AxisValue;
	rotation.Pitch = pitch > 0 ? FMath::Clamp(rotation.Pitch + AxisValue, 0.0f, 89.9f) : FMath::Clamp(rotation.Pitch + AxisValue, -89.9f, 0.0f);

	SetRelativeRotation(rotation);
}
void UCameraSpringArmComponent::Yaw(float AxisValue) 
{
	FRotator DeltaRotation(ForceInit);
	DeltaRotation.Yaw = (AxisValue);

	AddRelativeRotation(DeltaRotation);
}
void UCameraSpringArmComponent::ZoomInOut(float AxisValue) 
{
	TargetArmLength = FMath::Clamp(TargetArmLength + AxisValue * _zoomFactor, 200.0f, 400.0f);
}