// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ActorCondition.h"
#include "ACon_MovementMode.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TRAVELER_API UACon_MovementMode : public UActorCondition
{
	GENERATED_BODY()
	
public:
	virtual void VSetActor(AActor* actor);
	void SetValidateData(EMovementMode movementMode);
protected:
	virtual bool VTMValidate() override;

	UFUNCTION()
	void OnMovementModeChanged(ACharacter* character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

private:
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EMovementMode> _movementMode;

	UPROPERTY()
	ACharacter* _character;
};
