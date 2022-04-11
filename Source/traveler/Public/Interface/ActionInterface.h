// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/EnumActionType.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "ActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class TRAVELER_API IActionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual	UActionBase* VExecuteAction(EActionType actionType) PURE_VIRTUAL(UActionInterface::VExecuteAction, return nullptr;);

	UFUNCTION(BlueprintCallable)
	virtual UActionBlackBoard* VGetActionBlackBoard() PURE_VIRTUAL(UActionInterface::VGetActionBlackBoard, return nullptr;);

	UFUNCTION(BlueprintCallable)
	virtual bool VCheckActionIsInProgress(EActionType actionType) PURE_VIRTUAL(UActionInterface::VCheckActionIsInProgress, return nullptr;);
};
