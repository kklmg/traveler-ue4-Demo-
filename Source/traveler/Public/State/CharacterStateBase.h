// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "Actions/Action.h"
#include "CharacterStateBase.generated.h"

class UActionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UCharacterStateBase : public UState
{
	GENERATED_BODY()

public:
	void Initialize();

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
	UAction* _actionIdle;
	UAction* _actionMove;
	UAction* _actionSprint;
	UAction* _actionJump;
	UAction* _actionTarget;
	UAction* _actionDash;
};