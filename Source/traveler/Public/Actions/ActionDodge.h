// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "ActionDodge.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionDodge : public UAction
{
	GENERATED_BODY()
public:
	UActionDodge();

	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;

	UFUNCTION()
	void OnAnimationFinished(UAnimMontage* montage, bool interrupted);
private:
	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _dodgeSpeed;

	UPROPERTY(EditDefaultsOnly, Category = animation)
	UAnimMontage* _aniMontage;
};
