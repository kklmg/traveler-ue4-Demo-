// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ActorCondition.h"
#include "AC_MovementMode.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TRAVELER_API UAC_MovementMode : public UActorCondition
{
	GENERATED_BODY()
	
public:
	virtual bool VValidate() override;

	void SetValidateData(EMovementMode movementMode);
private:
	EMovementMode _movementMode;
};
