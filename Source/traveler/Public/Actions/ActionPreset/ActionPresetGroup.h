// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/EnumActionType.h"
#include "Enums/EnumProcessState.h"
#include "ActionPresetGroup.generated.h"

class UActionPreset;
class UActionComponent;

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class TRAVELER_API UActionPresetGroup : public UObject
{
	GENERATED_BODY()

public:
	void Init(ACharacter* character, UActionComponent* actionComp);
	bool IsActionAlive(EActionType actionType);
	EProcessState GetActionState(EActionType actionType);
	void ExecuteAction(EActionType actionType);
	void AbortAction(EActionType actionType);
	void AbortAllActions();
	void SwitchActionSet(UActionPreset* actionSet);
	void Tick(float deltaTime);

private:
	UPROPERTY(EditDefaultsOnly, Category = ActionPresetClasses)
	TArray<TSubclassOf<UActionPreset>> _actionPresetClasses;

	UPROPERTY()
	TArray<UActionPreset*> _actionPresetInstances;

	UPROPERTY()
	UActionPreset* _curActionSet;
};
