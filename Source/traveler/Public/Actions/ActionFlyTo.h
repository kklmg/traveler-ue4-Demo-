// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionFlyTo.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionFlyTo : public UActionBase
{
	GENERATED_BODY()
public:
	UActionFlyTo();

	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;

private:
	bool _GetDestination(FVector& outVector);

	UPROPERTY(EditDefaultsOnly, Category = speed)
	bool _bUpdateDestination;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _turnningSpeed;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _limitedRollDegree;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _limitedPitchDegree;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _rollDegreePerSecond;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _yawDegreePerSecond;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _pitchDegreePerSecond;

	FVector _destination;

	float _preRoll;

	float _resetFactor;
	float _resetFactorSpeed;


	float _YawTurnning(float flyingSpeed,FVector dirToDestination, FVector dirForward, float deltaTime);

	float ComputePitch();

	float GetBreakingDistance_Z(float offset, float curPitch, float pitchRate);
};
