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

	void Reset();

	void SetPitchRange(float pitchMin,float pitchMax);

	UFUNCTION(BlueprintCallable, Category = getter)
	float GetPitch01();

private:
	UPROPERTY(VisibleAnywhere, Category = pitch)
	float _pitchMin;
	UPROPERTY(VisibleAnywhere, Category = pitch)
	float _pitchMax;
	UPROPERTY(EditDefaultsOnly, Category = pitch)
	float _pitchMinDefault;
	UPROPERTY(EditDefaultsOnly, Category = pitch)
	float _pitchMaxDefault;

	UPROPERTY(EditAnywhere, Category = zoom)
	float _zoomMax;
	UPROPERTY(EditAnywhere, Category = zoom)
	float _zoomMin;
	UPROPERTY(EditAnywhere, Category = zoom)
	float _zoomFactor;
};
