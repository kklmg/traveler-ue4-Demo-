// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effet/EffectPlayerBase.h"
#include "EffectPlayer_Dissolve.generated.h"


USTRUCT(BlueprintType)
struct FEffectData_Dissolve
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> EffectActorClass;

	UPROPERTY()
	AActor* EffectActorIns;
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UEffectPlayer_Dissolve : public UEffectPlayerBase
{
	GENERATED_BODY()
public:
	UEffectPlayer_Dissolve(const FObjectInitializer& ObjectInitializer);

	virtual void VInitialize(AActor* owner, UMaterialInstanceDynamic* mid) override;

	virtual void VPlayEffect(uint8 effectOption);
	virtual void VStopEffect(uint8 effectOption);
	virtual void VTick(float deltaTime);

private:
	
	UPROPERTY(EditDefaultsOnly)
	FMaterialParameterInfo _matParamInfo_DissolveAmount;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _dissolveAmountCurve;

	UPROPERTY(EditDefaultsOnly)
	float _elapsedTime;

	UPROPERTY(EditDefaultsOnly)
	bool _bForward;

	UPROPERTY()
	float _dissolveAmount;

	UPROPERTY()
	float _duration;
};
