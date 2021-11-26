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
	void virtual Enter();
	void virtual Leave();

	bool TryGetActionInstance(FName actionName, UAction** outActionInstance);
	bool TryGetActionClass(FName actionName, TSubclassOf<UAction> outActionClass);

	virtual EMovementMode GetMovementMode();

	void MakeActionInstances();

private:
	UPROPERTY(VisibleAnyWhere)
	TMap<FName, UAction*> _mapActionInstaces;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UAction>> _arrayActionClasses;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EMovementMode> _movementMode;
};
