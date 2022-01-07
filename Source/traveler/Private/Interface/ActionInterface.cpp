// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/ActionInterface.h"
#include "Actions/ActionBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"

// Add default functionality here for any IActionInterface functions that are not pure virtual.


UActionBase* IActionInterface::VExecuteAction(EActionType actionType)
{
	UE_LOG(LogTemp, Warning, TEXT("IActionInterface::VExecuteAction is not implemented"));
	return nullptr;
}

UActionBlackBoard* IActionInterface::VGetActionBlackBoard()
{
	UE_LOG(LogTemp, Warning, TEXT("IActionInterface::VGetActionBlackBoard is not implemented"));
	return nullptr;
}
