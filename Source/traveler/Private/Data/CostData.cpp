// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CostData.h"


void UCostData::SetCost(EAttributeType attType, float cost)
{
	if (_mapCost.Contains(attType))
	{
		_mapCost[attType] = cost;
	}
	else
	{
		_mapCost.Add(attType,cost);
	}
}

void UCostData::AddCost(EAttributeType attType, float cost)
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

TArray<TPair<EAttributeType, float>> UCostData::GetCostArray()
{
	TArray<TPair<EAttributeType, float>> costArray;

	for(TPair<EAttributeType, float> pair : _mapCost)
	{
		costArray.Add(pair);
	}

	return costArray;
}