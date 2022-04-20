// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Status/EnumStatus.h"
#include "CostData.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCostData : public UObject
{
	GENERATED_BODY()
public:
	void AddCost(EStatusType attType, float cost);

	TArray<TPair<EStatusType, float>> GetCostArray();

private:
	UPROPERTY(EditAnywhere)
	TMap<EStatusType,float> _mapCost;
};
