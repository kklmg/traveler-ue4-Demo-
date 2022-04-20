// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraSpringArmComponent.generated.h"

class UAnimationModelBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UCameraSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	UCameraSpringArmComponent();

	void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	void Pitch(float AxisValue);
	void Yaw(float AxisValue);
	void ZoomInOut(float AxisValue);

	void ResetPitchLimit();

	void SetPitchLimit(float pitchMin,float pitchMax);

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
	float _zoomStep;

	UPROPERTY()
	UAnimationModelBase* _animationViewModel;
};
