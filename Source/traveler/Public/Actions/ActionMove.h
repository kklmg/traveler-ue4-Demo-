// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionMove.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionMove : public UActionBase
{
	GENERATED_BODY()

public:
	UActionMove();
public:
	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;
};
