// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CameraSpringArmComponent.h"
#include "Components/AnimControlComponent.h"
#include "Data/AnimationModelBase.h"

UCameraSpringArmComponent::UCameraSpringArmComponent()
{
	SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	bEnableCameraLag = false;
	//CameraLagSpeed = 3.0f;

	//
	SetAbsolute(false, true, true);

	//pitch
	_pitchMinDefault = -89.9f;
	_pitchMaxDefault = 89.9f;
	_pitchMin = _pitchMinDefault;
	_pitchMax = _pitchMaxDefault;

	//zoom 
	_zoomMax = 400;
	_zoomMin = 100;
	_zoomStep = 20;

	TargetArmLength = _zoomMax;
}

void UCameraSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	UAnimControlComponent* animControlComp = Cast<UAnimControlComponent>(GetOwner()->GetComponentByClass(UAnimControlComponent::StaticClass()));
	if(animControlComp)
	{
		_animationViewModel = animControlComp->GetAnimViewModel();
	}
}

void UCameraSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super:: TickComponent(DeltaTime,TickType,ThisTickFunction);
}

void UCameraSpringArmComponent::Pitch(float AxisValue)
{
	FRotator rotation = GetComponentRotation();
	float pitch = rotation.Pitch + AxisValue;
	rotation.Pitch = pitch > 0 ? FMath::Clamp(rotation.Pitch + AxisValue, 0.0f, _pitchMax) : FMath::Clamp(rotation.Pitch + AxisValue, _pitchMin, 0.0f);

	SetRelativeRotation(rotation);

	if (_animationViewModel)
	{
		_animationViewModel->SetFloat(NSAnimationDataKey::fCameraPitch, rotation.Pitch);
	}
}
void UCameraSpringArmComponent::Yaw(float AxisValue)
{
	FRotator DeltaRotation(ForceInit);
	DeltaRotation.Yaw = (AxisValue);

	AddRelativeRotation(DeltaRotation);
}
void UCameraSpringArmComponent::ZoomInOut(float AxisValue)
{
	TargetArmLength = FMath::Clamp(TargetArmLength + AxisValue * _zoomStep, _zoomMin, _zoomMax);
}

void UCameraSpringArmComponent::SetPitchLimit(float pitchMin, float pitchMax)
{
	_pitchMin = FMath::Max(pitchMin, _pitchMinDefault);
	_pitchMax = FMath::Min(pitchMax, _pitchMaxDefault);

	if(_animationViewModel)
	{
		_animationViewModel->SetFloat(NSAnimationDataKey::fCameraPitchMin, _pitchMin);
		_animationViewModel->SetFloat(NSAnimationDataKey::fCameraPitchMax, _pitchMax);
	}
}

void UCameraSpringArmComponent::ResetPitchLimit()
{
	_pitchMin = _pitchMinDefault;
	_pitchMax = _pitchMaxDefault;

	if (_animationViewModel)
	{
		_animationViewModel->SetFloat(NSAnimationDataKey::fCameraPitchMin, _pitchMin);
		_animationViewModel->SetFloat(NSAnimationDataKey::fCameraPitchMax, _pitchMax);
	}
}
