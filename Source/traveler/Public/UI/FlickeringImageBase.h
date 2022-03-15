// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "FlickeringImageBase.generated.h"

class UCompositeProcessBase;
/**
 * 
 */
UCLASS()
class TRAVELER_API UFlickeringImageBase : public UImage
{
	GENERATED_BODY()
public:
	void Initialize();
	void Tick(float deltaTime);

private:
	UPROPERTY(EditDefaultsOnly)
	float _flickeringTime;

	UPROPERTY(EditDefaultsOnly)
	float _coolingTime;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _opactiryCurve;

	float _remainingTime;

private:
	UCompositeProcessBase* _compositeProcess;
};
