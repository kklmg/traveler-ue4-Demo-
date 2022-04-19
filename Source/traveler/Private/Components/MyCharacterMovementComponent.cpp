// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Interface/StatusInterface.h"
#include "Interface/ActionInterface.h"
#include "Interface/AnimControlInterface.h"
#include "Interface/EventBrokerInterface.h"
#include "Event/ActorEventDataBase.h"
#include "Event/EventNames.h"

UMyCharacterMovementComponent::UMyCharacterMovementComponent()
{
}

FFlyingAbilityData& UMyCharacterMovementComponent::getFlyingAbilityData()
{
	return _FlyingAbilityData;
}

void UMyCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	_actionInterface = GetOwner<IActionInterface>();
	_statusInterface = GetOwner<IStatusInterface>();
	_eventBrokerInterface = GetOwner<IEventBrokerInterface>();

	if(_statusInterface && _actionInterface)
	{
		//set walking speed 
		MaxWalkSpeed = _statusInterface->VGetFinalValue(EStatusType::EStatus_WalkingSpeed);

		_actionInterface->VGetActionBlackBoard()->
			GetValueChangedDelegate_Bool(EActionDataKey::EACTD_WantToSprint).AddUObject(this, &UMyCharacterMovementComponent::OnCharacterWantToSprint);
	}

	IAnimControlInterface* animationCommunicator = GetOwner<IAnimControlInterface>();
	if (animationCommunicator)
	{
		_animationViewModel = animationCommunicator->VGetAnimationModel();
	}

	PublishMovementModeChangedEvent();
}

void UMyCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMyCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	if(_animationViewModel)
	{
		_animationViewModel->SetUInt8(NSAnimationDataKey::byteMovementMode, MovementMode);
	}
	PublishMovementModeChangedEvent();
}

void UMyCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (_animationViewModel)
	{
		_animationViewModel->SetVector(NSAnimationDataKey::vMovingVelocity, Velocity);
	}
}

void UMyCharacterMovementComponent::PublishMovementModeChangedEvent()
{
	if (_eventBrokerInterface)
	{
		UActorEventDataBase* eventData = NewObject<UActorEventDataBase>(this);
		eventData->SetActor(GetOwner());
		_eventBrokerInterface->VPublishEvent(NSEventNames::MovementModeChanged, eventData);
	}
}

void UMyCharacterMovementComponent::OnCharacterWantToSprint(bool wantToSprint)
{
	if (_statusInterface)
	{
		if (wantToSprint)
		{
			MaxWalkSpeed = _statusInterface->VGetFinalValue(EStatusType::EStatus_SprintingSpeed);
		}
		else
		{

			MaxWalkSpeed = _statusInterface->VGetFinalValue(EStatusType::EStatus_WalkingSpeed);
		}
	}
}
