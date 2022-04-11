// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionBase.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Interface/StatusInterface.h"
#include "Data/CostData.h"
#include "Interface/AnimControlInterface.h"


DEFINE_LOG_CATEGORY(LogAction);

UActionBase::UActionBase()
{
	_processState = EProcessState::EPS_UnInitialized;
	_bInstantAction = true;
	_actionName = FName(TEXT("UnKnown"));
	_actionType = EActionType::EACT_None;
	_costData = CreateDefaultSubobject<UCostData>(TEXT("CostData"));
}

void UActionBase::Initialize(UActionComponent* actionComponent, UActionBlackBoard* actionBlackBoard)
{
	_actionBlackBoard = actionBlackBoard;
	_actionComp = actionComponent;
	_actionOwner = actionComponent->GetOwner<ACharacter>();
	if (_actionOwner == false)
	{
		UE_LOG(LogTemp, Error, TEXT("no ation owner!"));
		return;
	}
	_statusInterface = Cast<IStatusInterface>(_actionOwner);

	//get animation view model
	IAnimControlInterface* animationCommunicator = Cast<IAnimControlInterface>(_actionOwner);
	if (animationCommunicator)
	{
		_animationViewModel = animationCommunicator->VGetAnimationModel();
	}

	_processState = EProcessState::EPS_ReadyToExecute;
	VTMInitialize();
}

void UActionBase::VTMInitialize()
{
}


void UActionBase::Pause()
{
	_processState = EProcessState::EPS_Paused;
}

FORCEINLINE void UActionBase::Execute()
{
	if (CanExecute() == false)
	{
		UE_LOG(LogAction, Warning, TEXT("Can't execute Action"));

		_processState = EProcessState::EPS_FAILED;
		return;
	}

	if(_statusInterface)
	{
		_statusInterface->VApplyCost(_costData);
	}

	VTMExecute();

	_processState = _bInstantAction ? EProcessState::EPS_SUCCEEDED : EProcessState::EPS_Running;
}

FORCEINLINE bool UActionBase::CanExecute()
{
	bool bEnoughResources = _statusInterface && _statusInterface->VIsRemainingValueEnough(_costData);

	return (_processState == EProcessState::EPS_ReadyToExecute && bEnoughResources && VTMCanExecute());
}

void UActionBase::Tick(float deltaTime)
{
	if (_processState == EProcessState::EPS_Running)
	{
		_elapsedTime += deltaTime;
		VTMTick(deltaTime);
	}
}

bool UActionBase::VTMCanExecute()
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
	if (_processState == EProcessState::EPS_Running)
	{
		_processState = EProcessState::EPS_Aborted;
	}
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
	return (_processState == EProcessState::EPS_SUCCEEDED || _processState == EProcessState::EPS_FAILED || _processState == EProcessState::EPS_Aborted);
}

FORCEINLINE EProcessState UActionBase::GetActionProcessState()
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

float UActionBase::GetElapsedTime()
{
	return _elapsedTime;
}

void UActionBase::SetActionProcessSucceed()
{
	_processState = EProcessState::EPS_SUCCEEDED;
	VOnActionCompleted();
}

void UActionBase::SetActionProcessFailed()
{
	_processState = EProcessState::EPS_FAILED;
	VOnActionCompleted();
}

FORCEINLINE UActionComponent* UActionBase::GetActionComponent()
{
	return _actionComp;
}

FORCEINLINE UCostData* UActionBase::GetCostData()
{
	return _costData;
}

FORCEINLINE UAnimationModelBase* UActionBase::GetAnimationViewModel()
{
	return _animationViewModel;
}

void UActionBase::VOnActionCompleted()
{
}

FORCEINLINE bool UActionBase::IsInstantAction()
{
	return _bInstantAction;
}