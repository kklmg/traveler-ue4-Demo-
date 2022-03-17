// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "MyDamageType.generated.h"

UENUM(BlueprintType)
enum class EElementalDamageType : uint8
{
	EEDT_None UMETA(DisplayName = "None"),
	EEDT_Physics UMETA(DisplayName = "Physics"),
	EEDT_Fire UMETA(DisplayName = "Fire"),
	EEDT_Water UMETA(DisplayName = "Water"),
	EEDT_Ice UMETA(DisplayName = "Ice"),
	EEDT_Electricity UMETA(DisplayName = "Electricity"),
	EEDT_Poison UMETA(DisplayName = "Poison"),
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UMyDamageType : public UDamageType
{
	GENERATED_BODY()
public:
	UMyDamageType();

	FName GetDamageTypeName();

public:
	UPROPERTY(EditDefaultsOnly)
	EElementalDamageType DamageType;

	UPROPERTY(EditDefaultsOnly)
	bool bIsContinuousDamage;

	UPROPERTY(EditDefaultsOnly)
	float BasicDamage;

	UPROPERTY(EditDefaultsOnly)
	float DamageHandleInterval;

	UPROPERTY(EditDefaultsOnly)
	float DamageHandleCount;
};
