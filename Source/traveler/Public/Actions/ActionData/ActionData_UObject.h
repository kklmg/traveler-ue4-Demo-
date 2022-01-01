// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionData/ActionDataBase.h"
#include "ActionData_UObject.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionData_UObject : public UActionDataBase
{
	GENERATED_BODY()
public:
	UObject* GetValue();
	void SetValue(UObject* value);
private:
	UObject* _value;
};
