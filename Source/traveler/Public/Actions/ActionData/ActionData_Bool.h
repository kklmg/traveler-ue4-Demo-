// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionData/ActionDataBase.h"
#include "ActionData_Bool.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionData_Bool : public UActionDataBase
{
	GENERATED_BODY()
	
public:
	bool GetValue();
	void SetValue(bool value);
private:
	bool _value;
};
