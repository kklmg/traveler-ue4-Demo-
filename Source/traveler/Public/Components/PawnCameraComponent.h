// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "PawnCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UPawnCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UPawnCameraComponent();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void DragCamera(FVector offset);

	void CancelDrag();

private:
	bool _isDragging;
	float _dragSpeed;
	float _factor;
	FVector _draggedLocation;
	FVector _originalLocation;
};
