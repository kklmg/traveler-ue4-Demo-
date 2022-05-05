// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/MyDelegates.h"
#include "EventBroker.generated.h"

USTRUCT()
struct TRAVELER_API FDelegateWrapper
{
	GENERATED_USTRUCT_BODY()
public:
	FMD_OnEventPublished OnEventPublished;

	UPROPERTY()
	UObject* CachedData;
};

USTRUCT()
struct TRAVELER_API FDelegateHandleData
{
	GENERATED_USTRUCT_BODY()
public:
	FDelegateHandleData();
	FDelegateHandleData(FName eventName, FDelegateHandle delegateHandle);

	FName EventName;
	FDelegateHandle DelegateHandle;
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UEventBroker : public UObject
{
	GENERATED_BODY()

public:
	bool RegisterEvent(FName eventName);
	bool ContainsRegisteredEvent(FName eventName);
	bool PublishEvent(FName eventName, UObject* data);
	FMD_OnEventPublished& RegisterAndGetEventDelegate(FName eventName);
	FMD_OnEventPublished* GetEventDelegate(FName eventName);

private:
	UPROPERTY()
	TMap<FName, FDelegateWrapper> _delegateMap;
};
