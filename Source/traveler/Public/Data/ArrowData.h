// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Damage/DamageData.h"
#include "ArrowData.generated.h"

class UNiagaraSystem;

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class TRAVELER_API UArrowData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* Effect_Head;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* Effect_HeadTrail;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* Effect_TailTrail;
	UPROPERTY(EditDefaultsOnly)
	FDamageData DamageData;
};
