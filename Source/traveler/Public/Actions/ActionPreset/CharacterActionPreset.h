// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionPreset/ActionPreset.h"
#include "CharacterActionPreset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UCharacterActionPreset : public UActionPreset
{
	GENERATED_BODY()
	
public:
	void virtual VInitialize(ACharacter* character, UActionComponent* actionComp) override;
	void virtual VEnter() override;
	void virtual VLeave() override;

private:
	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UActionBase> ActionMoveClass;

	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UActionBase> ActionSprintClass;

	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UActionBase> ActionJumpClass;

	UPROPERTY(EditAnywhere, Category = ActionClass)
	TSubclassOf<class UActionBase> ActionDodgeClass;
};
