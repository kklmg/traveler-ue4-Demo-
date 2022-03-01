// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "AnimatedImageBase.generated.h"

class UCurveVector;

/**
 * 
 */
UCLASS()
class TRAVELER_API UAnimatedImageBase : public UImage
{
	GENERATED_BODY()
public:
	UAnimatedImageBase();

	void Animate(float alpha);

private:
	UPROPERTY(EditAnyWhere)
	FVector2D _startLocation;

	UPROPERTY(EditAnyWhere)
	FVector2D _endLocation;

	UPROPERTY(EditAnyWhere)
	FRotator StartRotation;

	UPROPERTY(EditAnyWhere)
	FRotator EndRotation;

	UPROPERTY(EditAnyWhere)
	UCurveVector* _animCurve;
};
