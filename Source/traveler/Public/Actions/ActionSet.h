// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

	bool TryGetActionInstance(FName actionName, UAction** outActionInstance);
	bool TryGetActionClass(FName actionName, TSubclassOf<UAction> outActionClass);

	UAction* MakeActionInstance(FName actionName);
	void MakeAllActionInstances();

	void AddActionClass(TSubclassOf<UAction> actionClass);
private:
	UPROPERTY(VisibleAnyWhere)
	TMap<FName, UAction*> _mapActionInstaces;

	UPROPERTY(EditDefaultsOnly,Category = ActionClass)
	TArray<TSubclassOf<UAction>> _arrayActionClasses;
};
