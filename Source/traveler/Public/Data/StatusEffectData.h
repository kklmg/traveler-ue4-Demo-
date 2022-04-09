// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CombatData.h"
#include "StatusEffectData.generated.h"




UCLASS(Blueprintable)
class TRAVELER_API UStatusEffectData : public UObject
{
	GENERATED_BODY()

public:
	UStatusEffectData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatusEffect StatusEffectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementalType ElementalType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EffectDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> EffectActorClass;
};