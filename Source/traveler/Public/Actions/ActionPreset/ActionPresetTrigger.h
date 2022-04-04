// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Event/EventDataBase.h"
#include "ActionPresetTrigger.generated.h"


class UCompositeCondition;
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
	void Validate(UEventDataBase* eventData);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCompositeCondition> _conditionClass;

	UPROPERTY()
	UCompositeCondition* _conditionIns;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterActionPreset> _actionPresetClass;

	UPROPERTY()
	UCharacterActionPreset* _actionPresetIns;

	UPROPERTY()
	UActionComponent* _actionComponent;
};
