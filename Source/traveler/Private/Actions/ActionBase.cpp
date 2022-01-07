// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionBase.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"

DEFINE_LOG_CATEGORY(LogAction);

UActionBase::UActionBase()
{
	_state = EActionState::AS_UnInitialized;
	_bInstantAction = true;
	_actionName = TEXT("UnKnown");
	_actionType = EActionType::EACT_None;
}

void UActionBase::Initialize(UActionComponent* actionComponent, UActionBlackBoard* actionBlackBoard)
{
	_actionBlackBoard = actionBlackBoard;
	_actionComp = actionComponent;
	_actionOwner = actionComponent->GetOwner<ACharacter>();

	_state = EActionState::AS_ReadyToExecute;
}


void UActionBase::Pause()
{
	_state = EActionState::AS_Paused;
}

void UActionBase::VExecute() 
{
	if (_state != EActionState::AS_ReadyToExecute)
	{
		return;
	}
	_state = _bInstantAction ? EActionState::AS_SUCCEEDED : EActionState::AS_Running;
}

void UActionBase::VTick(float deltaTime) 
{
}

void UActionBase::Abort() 
{
	_state = EActionState::AS_Aborted;
}

FORCEINLINE bool UActionBase::CanStart()
{
	return _state == EActionState::AS_ReadyToExecute;
}

FORCEINLINE FName UActionBase::GetActionName()
{
	return _actionName;
}


EActionType UActionBase::GetActionType()
{
	return _actionType;
}

FORCEINLINE bool UActionBase::IsCompleted()
{
	return (_state == EActionState::AS_SUCCEEDED || _state == EActionState::AS_FAILED || _state == EActionState::AS_Aborted);
}

FORCEINLINE EActionState UActionBase::GetActionState()
{
	return _state;
}

FORCEINLINE ACharacter* UActionBase::GetActionOwner()
{
	return _actionOwner;
}


void UActionBase::SetActionState(EActionState state)
{
	_state = state;
}

FORCEINLINE bool UActionBase::IsInstantAction()
{
	return _bInstantAction;
}