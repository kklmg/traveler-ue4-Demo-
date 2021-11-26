// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "ActionRotate.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionRotate : public UAction
{
	GENERATED_BODY()
	
public:
	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;
};
