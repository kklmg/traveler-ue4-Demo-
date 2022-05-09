// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/EnumActionType.h"
#include "Enums/EnumProcessState.h"
#include "ActionPreset.generated.h"

class UActionBase;
class UActionComponent;
class UActionPresetGroup;
class UCompositeActorCondition;
class ACharacter;

/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UActionPreset : public UObject
{
	GENERATED_BODY()

public:
	void virtual VInitialize(ACharacter* character, UActionComponent* actionComp,UActionPresetGroup* actionPresetGroup);
	void virtual VEnter();
	void virtual VLeave();

	void Tick(float deltaTime);

	bool IsActionAlive(EActionType actionType);
	EProcessState GetActionState(EActionType actionType);
	void ExecuteAction(EActionType actionType);
	void AbortAction(EActionType actionType);
	void AbortAllActions();

protected:
	void MakeActionIns(TSubclassOf<UActionBase> actionClass,ACharacter* character, UActionComponent* actionComp);

	void ActivateThisActionSet(bool result);

private:
	UPROPERTY()
	TMap<EActionType, UActionBase*> _mapActionIns;

	UPROPERTY(EditDefaultsOnly,Category = ActionClass)
	TArray<TSubclassOf<UActionBase>> _arrayActionClasses;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCompositeActorCondition> _conditionClass;

	UPROPERTY()
	UCompositeActorCondition* _conditionIns;

	UPROPERTY()
	UActionPresetGroup* _actionPresetGroup;
};