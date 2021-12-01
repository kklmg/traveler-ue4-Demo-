// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Action.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"


UAction::UAction()
{
	_state = EActionState::AS_UnInitialized;
	_bInstantAction = true;
	_actionName = TEXT("UnKnown");
}

void UAction::Initialize(UActionComponent* actionComponent, UActionData* actionData)
{
	_actionData = actionData;
	_actionComp = actionComponent;
	_actionOwner = actionComponent->GetOwner<ACharacter>();

	_state = EActionState::AS_ReadyToExecute;
}


void UAction::Pause()
{
	_state = EActionState::AS_Paused;
}

void UAction::VExecute() 
{
	if (_state != EActionState::AS_ReadyToExecute)
	{
		return;
	}
	_state = _bInstantAction ? EActionState::AS_Finished : EActionState::AS_Running;
}

void UAction::VTick(float deltaTime) 
{
}

void UAction::Abort() 
{
	_state = EActionState::AS_Aborted;
}

bool UAction::CanStart() 
{
	return _state == EActionState::AS_ReadyToExecute;
}

FName UAction::GetActionName()
{
	return _actionName;
}

bool UAction::IsCompleted()
{
	return (_state == EActionState::AS_SUCCEEDED || _state == EActionState::AS_FAILED || _state == EActionState::AS_Aborted);
}

EActionState UAction::GetActionState()
{
	return _state;
}

ACharacter& UAction::GetActionOwner()
{
	return *_actionOwner;
}

bool UAction::IsInstantAction() 
{
	return _bInstantAction;
}