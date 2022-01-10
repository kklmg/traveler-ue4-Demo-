// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThrowerData.generated.h"


USTRUCT(BlueprintType)
struct FThrowerData 
{
	GENERATED_USTRUCT_BODY()

public:
	
	FThrowerData();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ThrowingRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Scale;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ConeAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCurveFloat* ScaleCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Life;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector Gravity;
};