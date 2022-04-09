// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/CompositeCondition.h"

bool UCompositeCondition::VValidate(UEventDataBase* eventData)
{
	for (UConditionBase* condition : _conditions)
	{
		if (!condition) continue;
		if (!condition->VValidate(eventData)) return false;
	}
	return true;
}

//TArray<FName> UCompositeCondition::VGetReactiveEventNames()
//{
//	TSet<FName> ReactiveEventNameSet;
//
//	for (auto condition : _conditions)
//	{
//		if (condition)
//		{
//			TArray<FName> eventNames = condition->VGetReactiveEventNames();
//			for (FName eventName : eventNames)
//			{
//				ReactiveEventNameSet.Add(eventName);
//			}
//		}
//	}
//
//	return ReactiveEventNameSet.Array();
//}

void UCompositeCondition::VInitialize()
{
	for (auto conditionClass : _conditionClasses)
	{
		if (conditionClass)
		{
			UConditionBase* conditionIns = NewObject<UConditionBase>(this, conditionClass);
			if(conditionIns)
			{
				conditionIns->VInitialize();
				_conditions.Add(conditionIns);
			}
		}
	}
}

void UCompositeCondition::Add(UConditionBase* condition)
{
	_conditions.Add(condition);
}
