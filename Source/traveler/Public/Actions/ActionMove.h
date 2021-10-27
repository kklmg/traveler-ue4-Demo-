// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "ActionMove.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionMove : public UAction
{
	GENERATED_BODY()

public:
	UActionMove();
	
	virtual void VUpdate(float deltaTime, AActor* actor, UActionData* data) override;
};
