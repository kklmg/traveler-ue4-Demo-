// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "FlickeringImageBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UFlickeringImageBase : public UImage
{
	GENERATED_BODY()
public:
	 void Tick(float deltaTime);

private:
	float remainingTime;
	float flickeringTime;
};
