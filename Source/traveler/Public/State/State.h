// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "State.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UState : public UObject
{
	GENERATED_BODY()

public:
	void virtual VEnter();
	void virtual VLeave();

	bool TryGetActionInstance(FName actionName, UAction** outActionInstance);
	bool TryGetActionClass(FName actionName, TSubclassOf<UAction> outActionClass);

	virtual EMovementMode GetMovementMode();

	UAction* MakeActionInstance(FName actionName);
	void MakeAllActionInstances();

	void AddActionClass(TSubclassOf<UAction> actionClass);
private:
	UPROPERTY(VisibleAnyWhere)
	TMap<FName, UAction*> _mapActionInstaces;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UAction>> _arrayActionClasses;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EMovementMode> _movementMode;
};
