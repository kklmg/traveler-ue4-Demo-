// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionWithAnimMontage.h"
#include "ActionDodge.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionDodge : public UActionWithAnimMontage
{
	GENERATED_BODY()
public:
	UActionDodge();

	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Force)
	float _dodgeForce;

	FVector _shiftDirection;
};
