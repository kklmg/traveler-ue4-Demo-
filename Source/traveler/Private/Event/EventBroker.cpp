// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/EventBroker.h"
#include "GameSystem/DebugMessageHelper.h"

FDelegateHandleData::FDelegateHandleData()
{
}

FDelegateHandleData::FDelegateHandleData(FName eventName, FDelegateHandle delegateHandle)
{
	EventName = eventName;
	DelegateHandle = delegateHandle;
}

FMD_UObjectSignature* UEventBroker::GetEventDelegate(FName eventName)
{
	return _delegateMap.Contains(eventName) ?
		&_delegateMap[eventName].OnEventPublished : nullptr;
}

bool UEventBroker::PublishEvent(FName eventName, UObject* data)
{
	if (_delegateMap.Contains(eventName))
	{
		_delegateMap[eventName].CachedData = data;
		_delegateMap[eventName].OnEventPublished.Broadcast(data);
		//UDebugMessageHelper::Messsage_String(TEXT("Published Event"), eventName.ToString());
		return true;
	}
	else
	{
		return false;
	}
}

UObject* UEventBroker::GetCachedEventData(FName eventName)
{
	return _delegateMap.Contains(eventName) ? _delegateMap[eventName].CachedData : nullptr;
}

FMD_UObjectSignature& UEventBroker::RegisterAndGetEventDelegate(FName eventName)
{
	if (_delegateMap.Contains(eventName))
	{
		return _delegateMap[eventName].OnEventPublished;
	}
	else
	{
		_delegateMap.Add(eventName, FDelegateWrapper());
		return _delegateMap[eventName].OnEventPublished;
	}
}

UEventBroker::UEventBroker()
{
}

bool UEventBroker::RegisterEvent(FName eventName)
{
	if (_delegateMap.Contains(eventName)) 
	{
		return false;
	}
	else
	{
		_delegateMap.Add(eventName, FDelegateWrapper());
		return true;
	}
}

bool UEventBroker::ContainsRegisteredEvent(FName eventName)
{
	return _delegateMap.Contains(eventName);
}
