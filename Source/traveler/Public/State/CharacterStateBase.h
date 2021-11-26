// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "CharacterStateBase.generated.h"

class AMyCharacter;
class UActionComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UCharacterStateBase : public UState
{
	GENERATED_BODY()

public:
	void virtual VEnter() override;
	void virtual VLeave() override;

private:
	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> ActionIdleClass;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> ActionMoveClass;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> ActionSprintClass;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> ActionJumpClass;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> ActionAimClass;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> ActionDodgeClass;
};
