// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionData/ActionDataBase.h"
#include "ActionData_FVector.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionData_FVector : public UActionDataBase
{
	GENERATED_BODY()
public:
	FVector GetValue();
	void SetValue(FVector value);
private:
	FVector _value;
};
