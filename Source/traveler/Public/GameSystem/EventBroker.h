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
	FOnEventPublished OnEventPublished;
};


UCLASS()
class TRAVELER_API UEventDataBase : public UObject
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UEventBroker : public UObject
{
	GENERATED_BODY()

public:
	FOnEventPublished& GetDelegate(FName eventName);
	void Publish(FName eventName, UEventDataBase* eventDataBase);

private:
	UPROPERTY()
	TMap<FName, FDelegateWrapper> _delegateMap;
};
