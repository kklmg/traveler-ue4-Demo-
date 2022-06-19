// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/CompositeCondition.h"

bool UCompositeCondition::VTMValidate()
{
	if (!Super::VOnValidated()) return false;

	for (UConditionBase* condition : _conditions)
	{
		if (!condition) return false;
		if (!condition->GetResult()) return false;
	}

	return true;
}


void UCompositeCondition::VTMInitialize()
{
	Super::VOnInitialized();

	for (auto conditionClass : _conditionClasses)
	{
		if (!conditionClass) continue;

		UConditionBase* conditionIns = NewObject<UConditionBase>(this, conditionClass);
		if (!conditionIns) continue;

		conditionIns->Initialize();
		conditionIns->OnValidatedDelegate.AddUObject(this, &UCompositeCondition::OnSubConditionChanged);
		_conditions.Add(conditionIns);
	}
}

void UCompositeCondition::Add(UConditionBase* condition)
{
	_conditions.Add(condition);
}

void UCompositeCondition::OnSubConditionChanged(bool result)
{
	this->OnValidatedDelegate.Broadcast(this->Validate());
}