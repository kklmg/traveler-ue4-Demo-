// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionDodge.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionDodge : public UActionBase
{
	GENERATED_BODY()
public:
	UActionDodge();

	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;

	UFUNCTION()
	void OnAnimMontageFinished(UAnimMontage* montage, bool interrupted);
private:

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _dodgeSpeed;

	UPROPERTY(EditDefaultsOnly, Category = animation)
	UAnimMontage* _aniMontage;

	FVector _shiftDirection;
};
