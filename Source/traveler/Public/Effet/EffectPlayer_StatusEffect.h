// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effet/EffectPlayerBase.h"
#include "EffectPlayer_StatusEffect.generated.h"


USTRUCT(BlueprintType)
struct FEffectData_StatusEffect
{
	GENERATED_USTRUCT_BODY()
public:
	FEffectData_StatusEffect();
	FEffectData_StatusEffect(FLinearColor& color);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor BlendColor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> EffectActorClass;

	UPROPERTY()
	AActor* EffectActorIns;
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UEffectPlayer_StatusEffect : public UEffectPlayerBase
{
	GENERATED_BODY()

public:
	UEffectPlayer_StatusEffect(const FObjectInitializer& ObjectInitializer);

	virtual void VPlayEffect(uint8 effectOption) override;
	virtual void VStopEffect(uint8 effectOption) override;
	virtual void VTick(float deltaTime) override;

private:
	void BlendColors();

private: 
	UPROPERTY(EditDefaultsOnly)
	FLinearColor _blendedColor;

	UPROPERTY(EditDefaultsOnly)
	float _alpha;

	UPROPERTY(EditDefaultsOnly)
	FMaterialParameterInfo _matParamInfo_Color;

	UPROPERTY(EditDefaultsOnly)
	TMap<EStatusEffect, FEffectData_StatusEffect> _effectData;

	UPROPERTY()
	TSet<EStatusEffect> _runningEffect;
};
