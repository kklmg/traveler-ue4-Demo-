// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionFaceTo.generated.h"

class UMyCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionFaceTo : public UActionBase
{
	GENERATED_BODY()
public:
	UActionFaceTo();

	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;
	virtual void VOnDead() override;

private:
	bool TryGetRequiredData();

	UPROPERTY()
	UMyCharacterMovementComponent* _myMovementComp;

	FVector _faceToDirection;
};
