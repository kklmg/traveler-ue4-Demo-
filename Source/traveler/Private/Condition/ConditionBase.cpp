// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ConditionBase.h"
#include "Event/EventDataBase.h"

void UConditionBase::VInitialize()
{
}

bool UConditionBase::GetResult()
{
	return _result;
}

bool UConditionBase::Validate()
{
	_result = VTMValidate();
	OnValidate.Broadcast(_result);
	return _result;
}

bool UConditionBase::VTMValidate()
{
	return true;
}


