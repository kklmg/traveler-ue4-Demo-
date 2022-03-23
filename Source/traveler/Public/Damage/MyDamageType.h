// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Data/CombatData.h"
#include "Data/StatusEffectData.h"
#include "MyDamageType.generated.h"


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
	EDamageType DamageType;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffectData> StatusEffectDataClass;
};
