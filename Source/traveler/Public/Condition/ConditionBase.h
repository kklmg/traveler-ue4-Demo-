// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/MyDelegates.h"
#include "ConditionBase.generated.h"

class UEventDataBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UConditionBase : public UObject
{
	GENERATED_BODY()

public:
	void Initialize();
	bool Validate();
	bool GetResult();

	template<typename TData>
	void Subscribe(TData* inUserObj, void (TData::* InFunc)(bool));

protected:
	virtual void VTMInitialize();
	virtual bool VTMValidate();

private:
	bool _cachedResult;

public:
	FMD_BoolSignature OnValidatedDelegate;
};

template<typename TData>
void UConditionBase::Subscribe(TData* inUserObj, void (TData::* InFunc)(bool))
{
	OnValidatedDelegate.AddUObject<TData>(inUserObj, InFunc);
}