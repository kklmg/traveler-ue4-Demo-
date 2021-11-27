// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/Action.h"
#include "ActionTakeOff.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionTakeOff : public UAction
{
	GENERATED_BODY()
	
public:
	UActionTakeOff();

public:
	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;
};
