// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionWithAnimMontage.h"
#include "ActionSpreadAttack.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionSpreadAttack : public UActionWithAnimMontage
{
	GENERATED_BODY()
public:
	UActionSpreadAttack();

	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	FName _boneName;

public:
	UFUNCTION()
	void OnEnterAniFrameAttack();

	void VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted) override;
};
