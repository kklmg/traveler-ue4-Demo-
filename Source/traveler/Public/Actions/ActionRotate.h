// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionRotate.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionRotate : public UActionBase
{
	GENERATED_BODY()
	
public:
	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;
};
