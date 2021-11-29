// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionIdle.h"
#include "Components/AttributeComponent.h"

UActionIdle::UActionIdle() 
{
	_actionName = ActionName::IDLE;
}


void UActionIdle::VExecute()
{
	Super::VExecute();

	//Get Attribute
	//UAttributeComponent* pAttributeComponent = _actionOwner->GetAttributeComponent();
	//check(pAttributeComponent != nullptr);

}

void UActionIdle::VTick(float deltaTime)
{
	Super::VTick(deltaTime);
}