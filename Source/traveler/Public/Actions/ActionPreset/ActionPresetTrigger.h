// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionPresetTrigger.generated.h"


class UCompositeActorCondition;
class UCharacterActionPreset;
class UActionComponent;

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class TRAVELER_API UActionPresetTrigger : public UObject
{
	GENERATED_BODY()
public:
	void Initiazlie(UActionComponent* actionComponent);

protected:
	UFUNCTION()
	void OnValidate(bool result);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCompositeActorCondition> _conditionClass;

	UPROPERTY()
	UCompositeActorCondition* _conditionIns;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterActionPreset> _actionPresetClass;

	UPROPERTY()
	UCharacterActionPreset* _actionPresetIns;

	UPROPERTY()
	UActionComponent* _actionComponent;
};
