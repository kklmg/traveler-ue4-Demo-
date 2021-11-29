// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionAscend.h"
#include "GameFramework/Character.h"


UActionAscend::UActionAscend()
{
	_actionName = ActionName::ASCEND;
}

void UActionAscend::VExecute()
{
	Super::VExecute();

	_actionOwner->AddMovementInput(FVector(0,0,1));
}

void UActionAscend::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}