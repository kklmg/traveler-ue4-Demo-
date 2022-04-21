// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionIdle.h"

UActionIdle::UActionIdle() 
{
	_actionName = NSNameAction::IDLE;
	_actionType = EActionType::EACT_Idle;
}


void UActionIdle::VTMExecute()
{
}

void UActionIdle::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}