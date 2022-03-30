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

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FLinearColor BlendColor;
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

	void Initialize(UMaterialInstanceDynamic* mid);

	void PlayEffect(EStatusEffect effectType);
	void StopEffect(EStatusEffect effectType);

	UFUNCTION(BlueprintPure)
	UMaterialInstanceDynamic* GetMaterial();

protected:

private:
	UPROPERTY(EditDefaultsOnly)
	FLinearColor _blendColor;

	UPROPERTY(EditDefaultsOnly)
	FMaterialParameterInfo _matColorParams;

	UPROPERTY(EditDefaultsOnly)
	TMap<EStatusEffect, FActorEffectData> _effectData;

	UPROPERTY()
	TSet<EStatusEffect> _runningEffect;

	UPROPERTY()
	UMaterialInstanceDynamic* _mid;
};