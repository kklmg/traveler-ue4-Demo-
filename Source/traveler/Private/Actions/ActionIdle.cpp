// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionIdle.h"
#include "Components/AttributeComponent.h"

UActionIdle::UActionIdle() 
{
	_actionName = ActionName::IDLE;
	_actionType = EActionType::EACT_Idle;
}


void UActionIdle::VTMExecute()
{
	//Get Attribute
	//UAttributeComponent* pAttributeComponent = _actionOwner->GetAttributeComponent();
	//check(pAttributeComponent != nullptr);

}

void UActionIdle::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);
}