// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionAscend.h"
#include "GameFramework/Character.h"


UActionAscend::UActionAscend()
{
	_actionName = ActionName::ASCEND;
	_actionType = EActionType::EACT_Ascend;
}

void UActionAscend::VTMExecute()
{
	GetActionOwner()->AddMovementInput(FVector(0,0,1));
}

void UActionAscend::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}