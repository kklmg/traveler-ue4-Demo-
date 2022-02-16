// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnCameraComponent.h"

// Sets default values for this component's properties
UPawnCameraComponent::UPawnCameraComponent() 
{
	PrimaryComponentTick.bCanEverTick = true;
	_dragStep = 0.2f;
}

void UPawnCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	_originalLocation = GetRelativeLocation();
}


// Called every frame
void UPawnCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_factor = FMath::Clamp(_factor + _dragStep * DeltaTime, 0.0f, 1.0f);
	FVector newLocation = FMath::Lerp(_originalLocation, _draggedLocation, _factor);
	SetRelativeLocation(newLocation);
}

void UPawnCameraComponent::DragCamera(FVector offset) 
{
	_draggedLocation = _originalLocation + offset;
	_dragStep = 4.0f;
}

void UPawnCameraComponent::CancelDrag() 
{
	_dragStep = -4.0f;
}
