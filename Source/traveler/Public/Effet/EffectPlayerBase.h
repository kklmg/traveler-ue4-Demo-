// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/EnumCombat.h"
#include "EffectPlayerBase.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class TRAVELER_API UEffectPlayerBase : public UObject
{
	GENERATED_BODY()

public:
	UEffectPlayerBase(const FObjectInitializer& ObjectInitializer);

	virtual void VInitialize(AActor* owner, UMaterialInstanceDynamic* mid);

	virtual void VPlayEffect(uint8 effectOption);
	virtual void VStopEffect(uint8 effectOption);
	virtual void VTick(float deltaTime);

	UFUNCTION(BlueprintPure)
	UMaterialInstanceDynamic* GetMaterial();

	UFUNCTION(BlueprintPure)
	AActor* GetOwner();

private:
	UPROPERTY()
	UMaterialInstanceDynamic* _mid;

	UPROPERTY()
	AActor* _owner;
};