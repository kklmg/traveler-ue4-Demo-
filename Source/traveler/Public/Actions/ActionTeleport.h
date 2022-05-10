// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionTeleport.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionTeleport : public UActionBase
{
	GENERATED_BODY()

public:
	UActionTeleport();

public:
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;
	
};
