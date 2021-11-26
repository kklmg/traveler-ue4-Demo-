// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "ActionJump.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionJump : public UAction
{
	GENERATED_BODY()
public:
	UActionJump();

	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;


	UFUNCTION()
	void OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
private:



	UPROPERTY(EditAnyWhere, Category = animation)
	UAnimMontage* _aniMontage;
};
