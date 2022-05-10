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
	bool TryGetDestData();

	UPROPERTY()
	UMyCharacterMovementComponent* _myMovementComp;

	UPROPERTY(EditDefaultsOnly)
	bool _bUpdateDestination;

	UPROPERTY(EditDefaultsOnly, Category = Tolerance)
	float _horizontalTolerance;

	UPROPERTY(EditDefaultsOnly, Category = Tolerance)
	float _verticalTolerance;

	FVector _destLocation;
	float _destRadius;
	float _destAltitude;
};
