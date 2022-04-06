// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CostData.h"




void UCostData::AddCost(EStatusType attType, float cost)
{
	if (_mapCost.Contains(attType))
	{
		_mapCost[attType] += cost;
	}
	else
	{
		_mapCost.Add(attType, cost);
	}
}

TArray<TPair<EStatusType, float>> UCostData::GetCostArray()
{
	TArray<TPair<EStatusType, float>> costArray;

	for(TPair<EStatusType, float> pair : _mapCost)
	{
		costArray.Add(pair);
	}

	return costArray;
}