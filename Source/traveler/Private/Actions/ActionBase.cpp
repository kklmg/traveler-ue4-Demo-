// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionBase.h"
#include "Components/ActionComponent.h"
#include "Components/StatusComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/ExtraTransformProviderComponent.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Data/CostData.h"


DEFINE_LOG_CATEGORY(LogAction);

UActionBase::UActionBase()
{
	_processState = EProcessState::EPS_UnInitialized;
	_bInstantAction = true;
	_actionName = FName(TEXT("UnKnown"));
	_actionType = EActionType::EACT_None;
	_costData = CreateDefaultSubobject<UCostData>(TEXT("CostData"));
}

void UActionBase::VInitialize(ACharacter* character, UActionComponent* actionComp, UActionBlackBoard* actionBlackBoard)
{
	check(character);
	check(actionComp);
	check(actionBlackBoard);

	_actionOwner = character;
	_actionComp = actionComp;
	_actionBlackBoard = actionBlackBoard;

	_statusComp = Cast<UStatusComponent>(_actionOwner->GetComponentByClass(UStatusComponent::StaticClass()));
	_animControlComp = Cast<UAnimControlComponent>(_actionOwner->GetComponentByClass(UAnimControlComponent::StaticClass()));
	_weaponComp = Cast<UWeaponComponent>(_actionOwner->GetComponentByClass(UWeaponComponent::StaticClass()));
	_exTransformProviderComp = Cast<UExtraTransformProviderComponent>(_actionOwner->GetComponentByClass(UExtraTransformProviderComponent::StaticClass()));

	_processState = EProcessState::EPS_ReadyToExecute;
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

	if(_statusComp)
	{
		_statusComp->ApplyCost(_costData);
	}

	VTMExecute();

	_processState = _bInstantAction ? EProcessState::EPS_SUCCEEDED : EProcessState::EPS_Running;
}

FORCEINLINE bool UActionBase::CanExecute()
{
	bool bEnoughResources = _statusComp && _statusComp->IsRemainingValueEnough(_costData);

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

FORCEINLINE_DEBUGGABLE UActionComponent* UActionBase::GetActionComp()
{
	return _actionComp;
}

FORCEINLINE_DEBUGGABLE UCostData* UActionBase::GetCostData()
{
	return _costData;
}

FORCEINLINE_DEBUGGABLE UAnimationModelBase* UActionBase::GetAnimationViewModel()
{
	return _animationViewModel;
}

FORCEINLINE_DEBUGGABLE UWeaponComponent* UActionBase::GetWeaponComp()
{
	return _weaponComp;
}

FORCEINLINE_DEBUGGABLE UAnimControlComponent* UActionBase::GetAnimControlComp()
{
	return _animControlComp;
}

FORCEINLINE_DEBUGGABLE UStatusComponent* UActionBase::GetStatusComp()
{
	return _statusComp;
}

FORCEINLINE_DEBUGGABLE UExtraTransformProviderComponent* UActionBase::GetExTransformProviderComp()
{
	return _exTransformProviderComp;
}

FORCEINLINE_DEBUGGABLE bool UActionBase::IsInstantAction()
{
	return _bInstantAction;
}

void UActionBase::VOnActionCompleted()
{
}

