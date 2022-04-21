// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/EnumActionType.h"
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
	void virtual VInitialize();
	void virtual VEnter();
	void virtual VLeave();

	UActionBase* GetActionInstance(EActionType actionType);
protected:
	void AddActionClassToMap(TSubclassOf<UActionBase> actionClass);
private:
	UPROPERTY()
	TMap<EActionType,TSubclassOf<UActionBase>> _mapActionClasses;

	UPROPERTY(EditDefaultsOnly,Category = ActionClass)
	TArray<TSubclassOf<UActionBase>> _arrayActionClasses;
};
