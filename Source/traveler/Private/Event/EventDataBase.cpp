// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/EventDataBase.h"

FDelegateHandleData::FDelegateHandleData()
{
}

FDelegateHandleData::FDelegateHandleData(FName eventName, FDelegateHandle delegateHandle)
{
	EventName = eventName;
	DelegateHandle = delegateHandle;
}