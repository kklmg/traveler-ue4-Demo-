// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCameraSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	UCameraSpringArmComponent();

public:
	void Pitch(float AxisValue);
	void Yaw(float AxisValue);
	void ZoomInOut(float AxisValue);

private:
	UPROPERTY(EditAnywhere, Category = zoom)
	float _zoomMax;
	UPROPERTY(EditAnywhere, Category = zoom)
	float _zoomMin;
	UPROPERTY(EditAnywhere, Category = zoom)
	float _zoomFactor;
};
