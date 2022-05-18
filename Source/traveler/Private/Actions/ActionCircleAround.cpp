// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionCircleAround.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "Components/StatusComponent.h"
#include "DrawDebugHelpers.h"

UActionCircleAround::UActionCircleAround()
{
	_processName = NSNameAction::FlyAroundPoint;
	_actionType = EActionType::EACT_FlyAround;

	_bIsInstantProcess = false;
}

bool UActionCircleAround::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	if (!TryGetData())
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Action Data"));
		return false;
	}

	_myMovementComp = Cast<UMyCharacterMovementComponent>
		(GetActionOwner()->GetComponentByClass(UMyCharacterMovementComponent::StaticClass()));
	if (_myMovementComp == nullptr)
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Movement component"));
		return false;
	}

	if (GetStatusComp() == nullptr)
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: no Status Component"));
		return false;
	}

	if (GetStatusComp()->GetFinalValue(EStatusType::EStatus_FlyingSpeed) == 0.0f)
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: Flying speed is zero"));
		return false;
	}
	return true;
}

void UActionCircleAround::VOnExecute()
{
	Super::VOnExecute();
}

void UActionCircleAround::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	if (!TryGetData())
	{
		SetProcessFailed();
	}

	//apply new velocity, Rotation
	//-------------------------------------------------------------------------------------------------------------
	_myMovementComp->RotateYaw(true, deltaTime, 1.0f);
	_myMovementComp->KeepSpeed(_normalizedSpeed, deltaTime);
}

bool UActionCircleAround::TryGetData()
{
	return GetActionBlackBoard()->TryGetData_Float(NSActionData::NormalizedSpeed::Name, _normalizedSpeed);
}