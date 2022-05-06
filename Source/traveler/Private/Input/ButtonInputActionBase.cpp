// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputActionBase.h"
#include "Components/ActionComponent.h"
#include "Components/EventBrokerComponent.h"


void UButtonInputActionBase::SetActor(AActor* actor)
{
	check(actor);
	_actor = actor;
	_actionComp = Cast<UActionComponent>(_actor->GetComponentByClass(UActionComponent::StaticClass()));
	
	//_actionComp = actionComp;
}

EActionType UButtonInputActionBase::GetActionType()
{
	return _actionType;
}

FORCEINLINE_DEBUGGABLE UActionComponent* UButtonInputActionBase::GetActionComp()
{
	return _actionComp;
}
