// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionData/ActionDataBase.h"
#include "ActionData_Int.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionData_Int : public UActionDataBase
{
	GENERATED_BODY()

public:
	int GetValue();
	void SetValue(int value);
private:
	int _value;
};
