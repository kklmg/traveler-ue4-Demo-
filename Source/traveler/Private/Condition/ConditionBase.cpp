// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ConditionBase.h"

void UConditionBase::Initialize()
{
	VOnInitialized();
	_cachedResult = Validate();
}

void UConditionBase::VOnInitialized()
{
}

bool UConditionBase::GetResult()
{
	return _cachedResult;
}

bool UConditionBase::Validate()
{
	_cachedResult = VOnValidated();
	OnValidatedDelegate.Broadcast(_cachedResult);
	return _cachedResult;
}

bool UConditionBase::VOnValidated()
{
	return true;
}


