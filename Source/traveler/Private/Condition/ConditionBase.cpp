// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ConditionBase.h"
#include "Event/EventDataBase.h"

void UConditionBase::Initialize()
{
	VTMInitialize();
	_cachedResult = Validate();
}

void UConditionBase::VTMInitialize()
{
}

bool UConditionBase::GetResult()
{
	return _cachedResult;
}

bool UConditionBase::Validate()
{
	_cachedResult = VTMValidate();
	OnValidated.Broadcast(_cachedResult);
	return _cachedResult;
}

bool UConditionBase::VTMValidate()
{
	return true;
}


