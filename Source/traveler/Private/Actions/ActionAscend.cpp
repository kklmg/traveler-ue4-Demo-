// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionAscend.h"
#include "GameFramework/Character.h"


UActionAscend::UActionAscend()
{
	_processName = NSNameAction::ASCEND;
	_actionType = EActionType::EACT_Ascend;
}

void UActionAscend::VOnExecute()
{
	GetActionOwner()->AddMovementInput(FVector(0, 0, 1));
}

void UActionAscend::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);
}