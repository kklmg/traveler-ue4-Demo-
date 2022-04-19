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

FMD_OnEventPublished& UEventBroker::GetDelegate(FName eventName)
{
	if(_delegateMap.Contains(eventName))
	{
		return _delegateMap[eventName].OnEventPublished;
	}
	else
	{
		_delegateMap.Add(eventName,FDelegateWrapper());
		return _delegateMap[eventName].OnEventPublished;
	}
}

void UEventBroker::Publish(FName eventName, UObject* data)
{
	if (_delegateMap.Contains(eventName))
	{
		_delegateMap[eventName].CachedData = data;
		_delegateMap[eventName].OnEventPublished.Broadcast(data);

		//UDebugMessageHelper::Messsage_String(TEXT("Published Event"), eventName.ToString());
	}
}
