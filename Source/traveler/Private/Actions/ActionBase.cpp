// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionBase.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Interface/StateInterface.h"

DEFINE_LOG_CATEGORY(LogAction);

UActionBase::UActionBase()
{
	_processState = EActionProcessState::EAPS_UnInitialized;
	_bInstantAction = true;
	_actionName = TEXT("UnKnown");
	_actionType = EActionType::EACT_None;
}

void UActionBase::Initialize(UActionComponent* actionComponent, UActionBlackBoard* actionBlackBoard)
{
	_actionBlackBoard = actionBlackBoard;
	_actionComp = actionComponent;
	_actionOwner = actionComponent->GetOwner<ACharacter>();

	_processState = EActionProcessState::EAPS_ReadyToExecute;
}


void UActionBase::Pause()
{
	_processState = EActionProcessState::EAPS_Paused;
}

FORCEINLINE bool UActionBase::VCanStart()
{
	return _processState == EActionProcessState::EAPS_ReadyToExecute;
}

void UActionBase::VExecute() 
{
	if (VCanStart() == false)
	{
		UE_LOG(LogAction,Warning,TEXT("Can't execute Action"));
		return;
	}
	_processState = _bInstantAction ? EActionProcessState::EAPS_SUCCEEDED : EActionProcessState::EAPS_Running;
}

void UActionBase::VTick(float deltaTime) 
{
}

void UActionBase::Abort() 
{
	_processState = EActionProcessState::EAPS_Aborted;
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
	return (_processState == EActionProcessState::EAPS_SUCCEEDED || _processState == EActionProcessState::EAPS_FAILED || _processState == EActionProcessState::EAPS_Aborted);
}

FORCEINLINE EActionProcessState UActionBase::GetActionProcessState()
{
	return _processState;
}

FORCEINLINE ACharacter* UActionBase::GetActionOwner()
{
	return _actionOwner;
}

FORCEINLINE UActionBlackBoard* UActionBase::GetActionBlackBoard()
{
	return _actionBlackBoard;
}

void UActionBase::SetActionSucceed()
{
	_processState = EActionProcessState::EAPS_SUCCEEDED;
	_VOnActionCompleted();
}

void UActionBase::SetActionFailed()
{
	_processState = EActionProcessState::EAPS_FAILED;
	_VOnActionCompleted();
}

void UActionBase::_VOnActionCompleted()
{
}

FORCEINLINE bool UActionBase::IsInstantAction()
{
	return _bInstantAction;
}