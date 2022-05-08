// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionBase.h"
#include "Components/ActionComponent.h"
#include "Components/StatusComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Data/CostData.h"


DEFINE_LOG_CATEGORY(LogAction);

UActionBase::UActionBase()
{
	_bIsInstantProcess = true;
	_processName = FName(TEXT("UnKnown"));
	_actionType = EActionType::EACT_None;
	_costData = CreateDefaultSubobject<UCostData>(TEXT("CostData"));
}

void UActionBase::SetActionData(ACharacter* character, UActionComponent* actionComp, UActionBlackBoard* actionBlackBoard)
{
	check(character);
	check(actionComp);
	check(actionBlackBoard);

	SetProcessAborted();

	_actionOwner = character;
	_actionComp = actionComp;
	_actionBlackBoard = actionBlackBoard;

	_statusComp = Cast<UStatusComponent>(_actionOwner->GetComponentByClass(UStatusComponent::StaticClass()));
	_exTransformProviderComp = Cast<UExTransformProviderComponent>(_actionOwner->GetComponentByClass(UExTransformProviderComponent::StaticClass()));
	_animControlComp = Cast<UAnimControlComponent>(_actionOwner->GetComponentByClass(UAnimControlComponent::StaticClass()));

	_bDataIsSet = true;
}



void UActionBase::VTMInit()
{
	_elapsedTime = 0.0f;
}

FORCEINLINE void UActionBase::VTMExecute()
{
	Super::VTMExecute();
	if(_statusComp)
	{
		_statusComp->TryApplyCost(_costData);
	}
}

FORCEINLINE bool UActionBase::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;
	if(!_bDataIsSet) return false;

	return _statusComp && _statusComp->IsRemainingPointEnough(_costData);
}

void UActionBase::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	_elapsedTime += deltaTime;
}

EActionType UActionBase::GetActionType()
{
	return _actionType;
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
	return _animControlComp ? _animControlComp->GetAnimationModel() : nullptr;
}

FORCEINLINE_DEBUGGABLE UAnimControlComponent* UActionBase::GetAnimControlComp()
{
	return _animControlComp;
}

FORCEINLINE_DEBUGGABLE UStatusComponent* UActionBase::GetStatusComp()
{
	return _statusComp;
}

FORCEINLINE_DEBUGGABLE UExTransformProviderComponent* UActionBase::GetExTransformProviderComp()
{
	return _exTransformProviderComp;
}




