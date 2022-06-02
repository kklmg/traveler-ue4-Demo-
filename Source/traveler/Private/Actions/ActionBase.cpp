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
#include "Interface/CharacterCameraInterface.h"


DEFINE_LOG_CATEGORY(LogAction);

UActionBase::UActionBase()
{
	_bIsInstantProcess = true;
	_processName = FName(TEXT("UnKnown"));
	_actionType = EActionType::EACT_None;
	_costData = CreateDefaultSubobject<UCostData>(TEXT("CostData"));
}

void UActionBase::VSetUpActionData(ACharacter* character, UActionComponent* actionComp)
{
	check(character);
	check(actionComp);

	_actionOwner = character;
	_actionComp = actionComp;
	_actionBlackBoard = actionComp->GetActionBlackBoard();

	_statusComp = Cast<UStatusComponent>(_actionOwner->GetComponentByClass(UStatusComponent::StaticClass()));
	_exTransformProviderComp = Cast<UExTransformProviderComponent>(_actionOwner->GetComponentByClass(UExTransformProviderComponent::StaticClass()));
	_animControlComp = Cast<UAnimControlComponent>(_actionOwner->GetComponentByClass(UAnimControlComponent::StaticClass()));
	_cameraInterface = Cast<ICharacterCameraInterface>(GetActionOwner());

	_bDataSettingIsFinished = true;
}



void UActionBase::VOnInit()
{
	_elapsedTime = 0.0f;
}

FORCEINLINE void UActionBase::VOnExecute()
{
	Super::VOnExecute();
	if(_statusComp)
	{
		_statusComp->TryApplyCost(_costData);
	}
}

FORCEINLINE bool UActionBase::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	if(!_bDataSettingIsFinished) return false;

	return _statusComp && _statusComp->IsRemainingPointEnough(_costData);
}

void UActionBase::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

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
	return _animControlComp ? _animControlComp->GetAnimViewModel() : nullptr;
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

ICharacterCameraInterface* UActionBase::GetCameraInterface()
{
	return _cameraInterface;
}




