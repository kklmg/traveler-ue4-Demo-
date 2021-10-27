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
	TSubclassOf<class UAction> _actionIdle;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> _actionMove;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> _actionSprint;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> _actionJump;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> _actionTarget;

	UPROPERTY(EditAnywhere, Category = Action)
	TSubclassOf<class UAction> _actionDash;
};
