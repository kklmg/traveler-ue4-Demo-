// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MyDelegates.h"
#include "EventDataBase.generated.h"

/**
 * 
 */

USTRUCT()
struct TRAVELER_API FDelegateWrapper
{
	GENERATED_USTRUCT_BODY()
public:
	FMD_OnEventPublished OnEventPublished;
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

UCLASS()
class TRAVELER_API UEventDataBool : public UEventDataBase
{
	GENERATED_BODY()
public:
	bool Value;
};

UCLASS()
class TRAVELER_API UEventDataInt32 : public UEventDataBase
{
	GENERATED_BODY()
public:
	int32 Value;
};

UCLASS()
class TRAVELER_API UEventDataUInt8 : public UEventDataBase
{
	GENERATED_BODY()
public:
	uint8 Value;
};

UCLASS()
class TRAVELER_API UEventDataFloat : public UEventDataBase
{
	GENERATED_BODY()
public:
	float Value;
};
