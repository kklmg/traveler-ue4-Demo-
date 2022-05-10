// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionCircleAround.generated.h"

class UMyCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionCircleAround : public UActionBase
{
	GENERATED_BODY()
public:
	UActionCircleAround();

	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;

private:
	bool TryGetData();

	UPROPERTY()
	UMyCharacterMovementComponent* _myMovementComp;

	float _normalizedSpeed;
};
