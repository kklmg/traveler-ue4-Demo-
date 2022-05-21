// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionDash.h"
#include "Actions/ActionDash.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameSystem/MyGameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Components/StatusComponent.h"
#include "AIController.h"

UActionDash::UActionDash()
{
	_processName = NSNameAction::sprint;
	_actionType = EActionType::EACT_Sprint;

	_bIsInstantProcess = false;
}

bool UActionDash::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	_myMovementComp = Cast<UMyCharacterMovementComponent>
		(GetActionOwner()->GetComponentByClass(UMyCharacterMovementComponent::StaticClass()));
	if (_myMovementComp == nullptr)
	{
		UE_LOG(LogAction, Warning, TEXT("Dash: No My Movement component"));
		return false;
	}

	return true;
}

void UActionDash::VOnExecute()
{
	Super::VOnExecute();

	if (!TryGetRequiredData())
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Dash : No Distance Data"));
	}

	_startLocation = GetActionOwner()->GetActorLocation();
	_myMovementComp->ToggleSprint(true);
}

void UActionDash::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	FVector curLocation = GetActionOwner()->GetActorLocation();
	if (FVector::DistSquared(_startLocation, curLocation) > _dashDistance * _dashDistance)
	{
		SetProcessSucceed();
	}

	GetActionOwner()->AddMovementInput(GetActionOwner()->GetActorForwardVector());
}

void UActionDash::VOnDead()
{
	Super::VOnDead();

	_myMovementComp->ToggleSprint(false);
}

bool UActionDash::TryGetRequiredData()
{
	if (GetActionBlackBoard()->TryGetData_Float(NSActionData::DashDistance::Name, _dashDistance) == false)
	{
		return false;
	}
	return true;
}
