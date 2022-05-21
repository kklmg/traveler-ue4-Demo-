// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionDash.generated.h"

class UMyCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionDash : public UActionBase
{
	GENERATED_BODY()
public:
	UActionDash();

	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;
	virtual void VOnDead() override;

private:
	bool TryGetRequiredData();

	UPROPERTY()
	UMyCharacterMovementComponent* _myMovementComp;

	FVector _startLocation;
	float _dashDistance;
};
