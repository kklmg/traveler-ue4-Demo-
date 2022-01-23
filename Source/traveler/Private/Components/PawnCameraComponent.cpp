// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnCameraComponent.h"

// Sets default values for this component's properties
UPawnCameraComponent::UPawnCameraComponent() 
{
	PrimaryComponentTick.bCanEverTick = true;

	_dragSpeed = 0.0f;
}

// Called every frame
void UPawnCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_factor = FMath::Clamp(_factor + _dragSpeed * DeltaTime, 0.0f, 1.0f);

	FVector newLocation = FMath::Lerp(_originalLocation, _draggedLocation, _factor);

	
	SetRelativeLocation(newLocation);
	if (_factor == 0.0f) 
	{
		_isDragging = false;
	}
}

void UPawnCameraComponent::DragCamera(FVector offset) 
{
	if (_isDragging == false)
	{
		_originalLocation = GetRelativeLocation();
		_draggedLocation = GetRelativeLocation() + offset;
		_dragSpeed = 4.0f;
		_isDragging = true;
	}
}

void UPawnCameraComponent::CancelDrag() 
{
	_dragSpeed = -4.0f;
}
