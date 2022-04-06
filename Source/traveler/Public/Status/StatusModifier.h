// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Status/EnumStatus.h"
#include "StatusModifier.generated.h"

class UStatusBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UStatusModifier : public UObject
{
	GENERATED_BODY()
public:
	void SetData(FName ModifierName, EStatusType statusType, float value);
	virtual float VGetDeltaValue(UStatusBase* statusBase);

	FName GetModifierName();
	EStatusType GetStatusType();

private:
	float _value;
	FName _modiferName;
	EStatusType _statusType;
};
