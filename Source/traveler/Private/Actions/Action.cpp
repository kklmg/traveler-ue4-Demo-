// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Action.h"
#include "Components/ActionComponent.h"


UAction::UAction() 
{
	_state = EActionState::AS_UNINITIALIZED;
	_actionName = TEXT("UnKnown");
}

void UAction::VInitialize()
{
	_state = EActionState::AS_UNINITIALIZED;
}

void UAction::Start(UActionComponent* actionComponent)
{
	check(actionComponent != nullptr)

	if (_state == EActionState::AS_UNINITIALIZED)
	{
		VBegin(actionComponent->GetOwner(), actionComponent->GetActionData());
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

FString UAction::GetActionName()
{
	return _actionName;
}


EActionState UAction::GetState() const
{
	return _state;
}

void UAction::SetState(EActionState state)
{
	_state = state;
}