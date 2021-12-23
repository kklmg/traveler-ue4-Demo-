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

void UAction::Initialize(UActionComponent* actionComponent, UActionData* actionData, UBlackboardComponent* actionblackBoard)
{
	_actionData = actionData;
	_actionComp = actionComponent;
	_actionBlackBoard = actionblackBoard;
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
	_state = _bInstantAction ? EActionState::AS_SUCCEEDED : EActionState::AS_Running;
}

void UAction::VTick(float deltaTime) 
{
}

void UAction::Abort() 
{
	_state = EActionState::AS_Aborted;
}

FORCEINLINE bool UAction::CanStart()
{
	return _state == EActionState::AS_ReadyToExecute;
}

FORCEINLINE FName UAction::GetActionName()
{
	return _actionName;
}

FORCEINLINE bool UAction::IsCompleted()
{
	return (_state == EActionState::AS_SUCCEEDED || _state == EActionState::AS_FAILED || _state == EActionState::AS_Aborted);
}

FORCEINLINE EActionState UAction::GetActionState()
{
	return _state;
}

FORCEINLINE ACharacter& UAction::GetActionOwner()
{
	return *_actionOwner;
}


void UAction::SetActionState(EActionState state)
{
	_state = state;
}

FORCEINLINE bool UAction::IsInstantAction()
{
	return _bInstantAction;
}