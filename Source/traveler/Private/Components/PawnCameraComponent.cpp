// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnCameraComponent.h"

// Sets default values for this component's properties
UPawnCameraComponent::UPawnCameraComponent() 
{
	_dragSpeed = 0.2f;
}

// Called every frame
void UPawnCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_factor = FMath::Clamp(_factor + _dragSpeed * DeltaTime, 0.0f, 1.0f);

	SetRelativeLocation(FMath::Lerp(_originalLocation, _draggedLocation, _factor));
}

void UPawnCameraComponent::BeginDragCamera(FVector offset) 
{
	_originalLocation = GetRelativeLocation();
	_draggedLocation = GetRelativeLocation() + offset;
	_dragSpeed = 0.25f;
}

void UPawnCameraComponent::CancelDrag() 
{
	_dragSpeed = -0.25f;
}