// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "Data/FlyingAbilityData.h"
#include "ActionFlyTo.generated.h"

class UMyCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionFlyTo : public UActionBase
{
	GENERATED_BODY()
public:
	UActionFlyTo();

	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;

private:
	bool TryGetRequiredData();

	UPROPERTY()
	UMyCharacterMovementComponent* _myMovementComp;

	UPROPERTY(EditDefaultsOnly)
	bool _bUpdateDestination;

	FVector _destLocation;
	float _keepingDistanceXY_Min;
	float _keepingDistanceXY_Max;
	float _destAltitude_Min;
	float _destAltitude_Max;
	bool _bFaceToDest;
	bool _bBrakeAtDest;
};
