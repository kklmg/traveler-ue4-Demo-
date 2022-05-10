// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionMove.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionMove : public UActionBase
{
	GENERATED_BODY()

public:
	UActionMove();
public:
	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UCostData* _sprintCost;

	FVector _movementInput;
};
