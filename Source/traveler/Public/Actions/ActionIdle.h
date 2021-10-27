// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "ActionIdle.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionIdle : public UAction
{
	GENERATED_BODY()
	
	virtual void VInitialize() override;

	virtual void VUpdate(float deltaTime, AActor* actor, UActionData* data) override;
};
