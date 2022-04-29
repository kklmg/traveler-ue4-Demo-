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

	virtual bool VTMCanExecute() override;
	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;

private:
	bool TryGetDestData();

	UPROPERTY()
	UMyCharacterMovementComponent* _myMovementComp;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	bool _bUpdateDestination;

	FVector _destLocation;
	float _destRadius;
	float _destAltitude;
};
