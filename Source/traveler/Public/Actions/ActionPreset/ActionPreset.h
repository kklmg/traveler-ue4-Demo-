// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumActionType.h"
#include "ActionPreset.generated.h"

class UActionBase;
/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UActionPreset : public UObject
{
	GENERATED_BODY()

public:
	void virtual VEnter();
	void virtual VLeave();

	bool TryGetActionInstance(EActionType actionType, UActionBase** outActionInstance);
	bool TryGetActionClass(EActionType actionType, TSubclassOf<UActionBase> outActionClass);

	UActionBase* MakeActionInstance(EActionType actionType);
	void MakeAllActionInstances();

	void AddActionClass(TSubclassOf<UActionBase> actionClass);
private:
	UPROPERTY()
	TMap<EActionType, UActionBase*> _mapActionInstaces;

	UPROPERTY(EditDefaultsOnly,Category = ActionClass)
	TArray<TSubclassOf<UActionBase>> _arrayActionClasses;
};
