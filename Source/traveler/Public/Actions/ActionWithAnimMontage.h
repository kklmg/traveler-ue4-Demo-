// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "Enums/EnumAnimation.h"
#include "ActionWithAnimMontage.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionWithAnimMontage : public UActionBase
{
	GENERATED_BODY()

public:
	UActionWithAnimMontage();

	virtual void VTMExecute() override;
	virtual void VTMOnDead() override;

	UFUNCTION()
	virtual void VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted);

private:
	UPROPERTY(EditDefaultsOnly, Category = animation)
	EAnimMontage _animMontageType;
};
