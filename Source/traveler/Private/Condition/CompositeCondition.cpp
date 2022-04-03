// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/CompositeCondition.h"

bool UCompositeCondition::VValidate()
{
	for (UConditionBase* condition : _conditions)
	{
		if (!condition) return false;
		if (!condition->VValidate()) return false;
	}
	return true;
}

void UCompositeCondition::Initialize()
{
	for (auto conditionClass : _conditionClasses)
	{
		if (conditionClass)
		{
			_conditions.Add(NewObject<UConditionBase>(this, conditionClass));
		}
	}
}

void UCompositeCondition::Add(UConditionBase* condition)
{
	_conditions.Add(condition);
}
