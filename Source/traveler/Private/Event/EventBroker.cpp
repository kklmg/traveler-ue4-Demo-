// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/EventBroker.h"
#include "GameSystem/DebugMessageHelper.h"

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

void UEventBroker::Publish(FName eventName, UEventDataBase* eventDataBase)
{
	if (_delegateMap.Contains(eventName))
	{
		//UDebugMessageHelper::Messsage_String(TEXT("Published Event"), eventName.ToString());
		_delegateMap[eventName].OnEventPublished.Broadcast(eventDataBase);
	}
}
