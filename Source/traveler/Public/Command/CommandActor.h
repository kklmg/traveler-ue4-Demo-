// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command/CommandBase.h"
#include "CommandActor.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCommandActor : public UCommandBase
{
	GENERATED_BODY()
	
public:
	void Initialize(AActor* actor);
protected:
	AActor* _actor;
};
