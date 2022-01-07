// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionAscend.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionAscend : public UActionBase
{
	GENERATED_BODY()
	
public:
	UActionAscend();

public:
	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;
};
