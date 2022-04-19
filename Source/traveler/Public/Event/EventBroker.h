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
	FMD_OnEventPublished& GetDelegate(FName eventName);
	void Publish(FName eventName, UObject* data);

private:
	UPROPERTY()
	TMap<FName, FDelegateWrapper> _delegateMap;
};
