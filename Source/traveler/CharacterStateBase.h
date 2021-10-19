// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "Action/Action.h"
#include "CharacterStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCharacterStateBase : public UState
{
	GENERATED_BODY()
public:
	virtual void Move();
	virtual void Sprint();
	virtual void Jump();
	virtual void Target();
	virtual void Dash();

private:
	UPROPERTY(EditAnywhere)
	UAction* _actionMove;

	UPROPERTY(EditAnywhere)
	UAction* _actionSprint;

	UPROPERTY(EditAnywhere)
	UAction* _actionJump;

	UPROPERTY(EditAnywhere)
	UAction* _actionTarget;

	UPROPERTY(EditAnywhere)
	UAction* _actionDash;
};
