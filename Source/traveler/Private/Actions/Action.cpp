// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Action.h"
#include "Components/ActionComponent.h"
#include "Character/MyCharacter.h"


UAction::UAction()
{
	_state = EActionState::AS_UNINITIALIZED;
	_actionName = TEXT("UnKnown");
}

void UAction::VInitialize(ACharacter* actionOwner)
{
	_state = EActionState::AS_UNINITIALIZED;
	_actionOwner = actionOwner;
}

void UAction::Start(UActionComponent* actionComponent)
{
	check(actionComponent != nullptr)

		if (_state == EActionState::AS_UNINITIALIZED || _state == EActionState::AS_FINISHED)
		{
			VBegin(actionComponent->GetOwner(), actionComponent->GetActionData());
		}

	_state = EActionState::AS_RUNNING;
	actionComponent->AddToLoop(this);

}

void UAction::Pause()
{

}


void UAction::Abort() 
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


EActionState UAction::GetState() const
{
	return _state;
}

void UAction::SetState(EActionState state)
{
	_state = state;
}

ACharacter& UAction::GetActionOwner()
{
	return *_actionOwner;
}

bool UAction::IsInstantAction() 
{
	return true;
}