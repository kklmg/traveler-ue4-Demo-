// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Status/EnumStatus.h"
#include "Status/StatusTableRow.h"
#include "Data/MyDelegates.h"
#include "StatusBase.generated.h"


class IEventBrokerInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDMD_OnFloatValueChanged, float, PreviousValue, float, NewValue);

/**
 * 
 */
UCLASS(BlueprintType)
class TRAVELER_API UStatusBase : public UObject
{
	GENERATED_BODY()
public:
	UStatusBase();

	virtual void VInitialize(const FStatusTableRow& tableRow, int32 level = 1);
	
	UFUNCTION(BlueprintPure)
	float GetPrimaryValue();

	UFUNCTION(BlueprintPure)
	float GetBasicValue();

	UFUNCTION(BlueprintPure)
	float GetFinalValue();

	UFUNCTION(BlueprintPure)
	EStatusType GetStatusType();

	UFUNCTION(BlueprintPure)
	FText GetText();

protected:
	virtual void VOnLevelUp(int32 level);
	void ComputeFinalValue();

private:
	EStatusType _statusType;
	FText _statusText;
	float _growth;

	float _primaryValue;
	float _basicValue;
	float _finalValue;

public:
	UPROPERTY(BlueprintAssignable)
	FDMD_OnFloatValueChanged OnBasicValueChanged;

	UPROPERTY(BlueprintAssignable)
	FDMD_OnFloatValueChanged OnFinalValueChanged;
};