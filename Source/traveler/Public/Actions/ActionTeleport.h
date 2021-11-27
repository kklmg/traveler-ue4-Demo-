// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "ActionTeleport.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionTeleport : public UAction
{
	GENERATED_BODY()

public:
	UActionTeleport();

public:
	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;
	
};
