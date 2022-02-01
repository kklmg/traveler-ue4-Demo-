// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionBase.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Interface/StateInterface.h"
#include "Interface/AttributeInterface.h"
#include "Interface/AnimationModelProvider.h"

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
	if(_actionOwner==false)
	{
		UE_LOG(LogTemp, Error, TEXT("no ation owner!"));
		return;
	}
	_stateInterface = Cast<IStateInterface>(_actionOwner);	
	_attributeInterface = Cast<IAttributeInterface>(_actionOwner);
	_animationModelProviderInterface = Cast<IAnimationModelProvider>(_actionOwner);
	
	_processState = EActionProcessState::EAPS_ReadyToExecute;

	VTMInitialize();
}

void UActionBase::VTMInitialize()
{
}


void UActionBase::Pause()
{
	_processState = EActionProcessState::EAPS_Paused;
}

FORCEINLINE void UActionBase::Execute()
{
	if (CanStart() == false)
	{
		UE_LOG(LogAction, Warning, TEXT("Can't execute Action"));

		_processState = EActionProcessState::EAPS_FAILED;
		return;
	}

	VTMExecute();

	_processState = _bInstantAction ? EActionProcessState::EAPS_SUCCEEDED : EActionProcessState::EAPS_Running;
}

FORCEINLINE bool UActionBase::CanStart()
{
	return (_processState == EActionProcessState::EAPS_ReadyToExecute && VTMCanStart());
}

void UActionBase::Tick(float deltaTime)
{
	VTMTick(deltaTime);
}

bool UActionBase::VTMCanStart()
{
	return true;
}

void UActionBase::VTMExecute() 
{
}

void UActionBase::VTMTick(float deltaTime) 
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

void UActionBase::SetActionProcessSucceed()
{
	_processState = EActionProcessState::EAPS_SUCCEEDED;
	VOnActionCompleted();
}

void UActionBase::SetActionProcessFailed()
{
	_processState = EActionProcessState::EAPS_FAILED;
	VOnActionCompleted();
}

void UActionBase::VOnActionCompleted()
{
}

FORCEINLINE bool UActionBase::IsInstantAction()
{
	return _bInstantAction;
}