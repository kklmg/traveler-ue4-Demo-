// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConditionBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnValidateCondition, bool);

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
	bool Validate();
	bool GetResult();
protected:
	virtual bool VTMValidate();

private:
	bool _result;

public:
	FOnValidateCondition OnValidate;
};



