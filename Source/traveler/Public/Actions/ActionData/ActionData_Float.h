// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionData/ActionDataBase.h"
#include "ActionData_Float.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionData_Float : public UActionDataBase
{
	GENERATED_BODY()
	
public:
	float GetValue();
	void SetValue(float value);
private:
	float _value;
};
