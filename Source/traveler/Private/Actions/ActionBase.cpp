// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionBase.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"

DEFINE_LOG_CATEGORY(LogAction);

UActionBase::UActionBase()
{
	_state = EActionProcessState::EAPS_UnInitialized;
	_bInstantAction = true;
	_actionName = TEXT("UnKnown");
	_actionType = EActionType::EACT_None;
}

void UActionBase::Initialize(UActionComponent* actionComponent, UActionBlackBoard* actionBlackBoard)
{
	_actionBlackBoard = actionBlackBoard;
	_actionComp = actionComponent;
	_actionOwner = actionComponent->GetOwner<ACharacter>();

	_state = EActionProcessState::EAPS_ReadyToExecute;
}


void UActionBase::Pause()
{
	_state = EActionProcessState::EAPS_Paused;
}

void UActionBase::VExecute() 
{
	if (CanStart() == false)
	{
		return;
	}
	_state = _bInstantAction ? EActionProcessState::EAPS_SUCCEEDED : EActionProcessState::EAPS_Running;
}

void UActionBase::VTick(float deltaTime) 
{
}

void UActionBase::Abort() 
{
	_state = EActionProcessState::EAPS_Aborted;
}

FORCEINLINE bool UActionBase::CanStart()
{
	return _state == EActionProcessState::EAPS_ReadyToExecute;
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
	return (_state == EActionProcessState::EAPS_SUCCEEDED || _state == EActionProcessState::EAPS_FAILED || _state == EActionProcessState::EAPS_Aborted);
}

FORCEINLINE EActionProcessState UActionBase::GetActionProcessState()
{
	return _state;
}

FORCEINLINE ACharacter* UActionBase::GetActionOwner()
{
	return _actionOwner;
}


void UActionBase::SetActionState(EActionProcessState state)
{
	_state = state;
}

FORCEINLINE bool UActionBase::IsInstantAction()
{
	return _bInstantAction;
}