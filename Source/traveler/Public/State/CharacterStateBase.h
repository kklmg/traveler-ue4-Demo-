// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "Actions/Action.h"
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
	void Initialize(AMyCharacter *character);

	void Idle(UActionComponent* actionComponent);
	void Move(UActionComponent* actionComponent);
	void Sprint(UActionComponent* actionComponent);
	void Jump(UActionComponent* actionComponent);
	void Target(UActionComponent* actionComponent);
	void Dash(UActionComponent* actionComponent);

public:
	void virtual Enter() override;
	void virtual Leave() override;

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
	TSubclassOf<class UAction> ActionTargetClass;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> ActionDashClass;

private:
	UPROPERTY()
	UAction* _actionIdle;
	UPROPERTY()
	UAction* _actionMove;
	UPROPERTY()
	UAction* _actionSprint;
	UPROPERTY()
	UAction* _actionJump;
	UPROPERTY()
	UAction* _actionTarget;
	UPROPERTY()
	UAction* _actionDash;
};
