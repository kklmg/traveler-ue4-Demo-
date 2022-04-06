// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Status/StatusBase.h"
#include "BasicStatus.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TRAVELER_API UBasicStatus : public UStatusBase
{
	GENERATED_BODY()
public:

	virtual void VInitialize(const FStatusTableRow& tableRow, int32 level = 1) override;

	void Tick(float deltaTime);

	UFUNCTION(BlueprintPure)
	float GetRemainingValue();

	UFUNCTION(BlueprintPure)
	float GetPercentage();

	void ApplyValueChange(float deltaValue, bool bResetRecoveryTimer = true);

	virtual void VOnLevelUp(int32 level);
private:

	UPROPERTY(EditDefaultsOnly)
	float _remainingValue;

	UPROPERTY(EditDefaultsOnly)
	float _recovery;

	float _elapsedTimeFromLastRecover;
	float _elapsedTimeFromLastValueChanged;

public:
	UPROPERTY(BlueprintAssignable)
	FDMD_OnFloatValueChanged OnRemainingValueChanged;
};
