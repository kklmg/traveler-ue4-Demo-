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

	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnDead() override;

	UFUNCTION()
	virtual void VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted);

protected:
	UPROPERTY(EditDefaultsOnly, Category = animation)
	EAnimMontageKey _animMontageType;
};
