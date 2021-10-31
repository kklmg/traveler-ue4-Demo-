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
	virtual void VBegin(AActor* actor, UActionData* actionData) override;

	virtual void VUpdate(float deltaTime, AActor* actor, UActionData* data) override;
};