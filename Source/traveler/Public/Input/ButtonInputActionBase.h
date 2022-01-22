// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "Interface/ActionInterface.h"
#include "ButtonInputActionBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputActionBase : public UButtonInputBase
{
	GENERATED_BODY()
public:
	void Initialize(IActionInterface* actionInterface);

	EActionType GetActionType();

protected:
	IActionInterface* _actionInterface;

	UPROPERTY(EditDefaultsOnly)
	EActionType _actionType;
};
