// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/CombatData.h"
#include "EffectPlayerBase.generated.h"


USTRUCT(BlueprintType)
struct FActorEffectData
{
	GENERATED_USTRUCT_BODY()
public:
	FActorEffectData();
	FActorEffectData(FLinearColor color);

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
UCLASS(Blueprintable, BlueprintType)
class TRAVELER_API UEffectPlayerBase : public UObject
{
	GENERATED_BODY()
	
public:
	UEffectPlayerBase();

	void Initialize(AActor* owner,UMaterialInstanceDynamic* mid);

	void PlayEffect(EStatusEffect effectType);
	void StopEffect(EStatusEffect effectType);

	UFUNCTION(BlueprintPure)
	UMaterialInstanceDynamic* GetMaterial();

protected:
	void ApplyBlendedColor();

private:
	UPROPERTY(EditDefaultsOnly)
	FLinearColor _blendedColor;

	UPROPERTY(EditDefaultsOnly)
	float _alpha;

	UPROPERTY(EditDefaultsOnly)
	FMaterialParameterInfo _matColorParams;

	UPROPERTY(EditDefaultsOnly)
	TMap<EStatusEffect, FActorEffectData> _effectData;

	UPROPERTY()
	TSet<EStatusEffect> _runningEffect;

	UPROPERTY()
	UMaterialInstanceDynamic* _mid;

	UPROPERTY()
	AActor* _owner;
};