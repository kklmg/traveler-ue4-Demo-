// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/EnumCombat.h"
#include "DamageData.generated.h"

class UStatusEffectData;

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class TRAVELER_API UDamageData : public UObject
{
	GENERATED_BODY()
public:
	UDamageData();

public:
	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	EElementalType ElementalType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatusEffectData> StatusEffectDataClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageTypeClass;
};
