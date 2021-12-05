// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command/CommandActor.h"
#include "CommandFreezeTime.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCommandFreezeTime : public UCommandActor
{
	GENERATED_BODY()

public:
	virtual void VExecute() final;
	virtual void VUndo() final;
};
