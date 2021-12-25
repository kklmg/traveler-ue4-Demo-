// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "ActionWithAnimMontage.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionWithAnimMontage : public UAction
{
	GENERATED_BODY()

public:
	UActionWithAnimMontage();

	virtual void VExecute() override;

	UFUNCTION()
	virtual void VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted);

private:
	UPROPERTY(EditDefaultsOnly, Category = animation)
	UAnimMontage* _aniMontage;
	
};
