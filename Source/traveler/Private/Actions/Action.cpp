// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Action.h"
#include "Components/ActionComponent.h"



void UAction::Start(UActionComponent* actionComponent)
{
	if (_state == EActionState::AS_UNINITIALIZED)
	{
		VInitialize();
	}

	actionComponent->AddToLoop(this);
	_state = EActionState::AS_RUNNING;
}

void UAction::Pause()
{

}


void UAction::Stop() 
{
}

bool UAction::CanStart() 
{
	return _state != EActionState::AS_RUNNING;
}

FName UAction::GetActionName()
{
	return _actionName;
}


void UAction::VInitialize()
{

}

void UAction::VUpdate(float deltaTime,AActor* actor, UActionData* data)
{

}

EActionState UAction::GetState() const
{
	return _state;
}

void UAction::SetState(EActionState state)
{
	_state = state;
}