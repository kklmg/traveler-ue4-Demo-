// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UState : public UObject
{
	GENERATED_BODY()

public:
	void virtual Enter();
	void virtual Leave();
};
