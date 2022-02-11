// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumAttributeType.h"
#include "CostData.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCostData : public UObject
{
	GENERATED_BODY()
public:
	void SetCost(EAttributeType attType, float cost);
	void AddCost(EAttributeType attType, float cost);

	TArray<TPair<EAttributeType, float>> GetCostArray();

private:
	UPROPERTY(EditAnywhere)
	TMap<EAttributeType,float> _mapCost;
};
