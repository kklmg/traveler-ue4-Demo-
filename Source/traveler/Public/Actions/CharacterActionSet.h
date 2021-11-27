// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionSet.h"
#include "CharacterActionSet.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UCharacterActionSet : public UActionSet
{
	GENERATED_BODY()
	
public:
	void virtual VEnter() override;
	void virtual VLeave() override;

private:
	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UAction> ActionIdleClass;

	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UAction> ActionMoveClass;

	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UAction> ActionSprintClass;

	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UAction> ActionJumpClass;

	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UAction> ActionAimClass;

	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UAction> ActionDodgeClass;
};
