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

	void Initialize();

	void Animate(float alpha);

private:
	UPROPERTY()
	FVector2D _startLocation;

	UPROPERTY()
	float _startAngle;

	UPROPERTY(EditAnyWhere, category = AnimData)
	FVector2D _endLocation;

	UPROPERTY(EditAnyWhere, category = AnimData)
	float _endAngle;

	UPROPERTY(EditAnyWhere, category = AnimData)
	UCurveVector* _animCurve;
};
