// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MyDelegates.h"
#include "EventDataBase.generated.h"

/**
 * 
 */

namespace NEventNames
{
	const FName MovementModeChanged = FName(TEXT("MovementModeChanged"));


}

USTRUCT()
struct TRAVELER_API FDelegateWrapper
{
	GENERATED_USTRUCT_BODY()
public:
	FOnEventPublished OnEventPublished;
};

USTRUCT()
struct TRAVELER_API FDelegateHandleData
{
	GENERATED_USTRUCT_BODY()
public:
	FDelegateHandleData();
	FDelegateHandleData(FName eventName,FDelegateHandle delegateHandle);

	FName EventName;
	FDelegateHandle DelegateHandle;
};


UCLASS()
class TRAVELER_API UEventDataBase : public UObject
{
	GENERATED_BODY()
};

