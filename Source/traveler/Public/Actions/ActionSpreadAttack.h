// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "ActionSpreadAttack.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionSpreadAttack : public UAction
{
	GENERATED_BODY()
public:
	UActionSpreadAttack();

	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;
//private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAnimMontage *_animMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName _boneName;
};
