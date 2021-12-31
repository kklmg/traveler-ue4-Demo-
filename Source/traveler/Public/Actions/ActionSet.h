// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumActionType.h"
#include "ActionSet.generated.h"

class UAction;
/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UActionSet : public UObject
{
	GENERATED_BODY()

public:
	void virtual VEnter();
	void virtual VLeave();

	bool TryGetActionInstance(EActionType actionType, UAction** outActionInstance);
	bool TryGetActionClass(EActionType actionType, TSubclassOf<UAction> outActionClass);

	UAction* MakeActionInstance(EActionType actionType);
	void MakeAllActionInstances();

	void AddActionClass(TSubclassOf<UAction> actionClass);
private:
	UPROPERTY(VisibleAnyWhere)
	TMap<EActionType, UAction*> _mapActionInstaces;

	UPROPERTY(EditDefaultsOnly,Category = ActionClass)
	TArray<TSubclassOf<UAction>> _arrayActionClasses;
};
