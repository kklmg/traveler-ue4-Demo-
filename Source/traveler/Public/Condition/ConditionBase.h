// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
	virtual void VInitialize();
	virtual bool VValidate(UEventDataBase* eventData) PURE_VIRTUAL(UConditionBase::VValidate, return false;);
	virtual TArray<FName> VGetReactiveEventNames();
};
