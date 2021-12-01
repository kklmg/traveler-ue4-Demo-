// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "ActionFlyTo.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionFlyTo : public UAction
{
	GENERATED_BODY()
public:
	UActionFlyTo();

	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _flyingSpeed;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _limitedRollDegree;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _rollDegreePerSecond;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _yawDegreePerSecond;

	FVector _destination;

	float _preRoll;


	//void _TurnTo();
};
