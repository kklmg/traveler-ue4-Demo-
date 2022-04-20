// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ActionComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Data/ObjectData.h"
#include "Event/EventNames.h"
#include "Data/AnimationModelBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"

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

	_actionComp = Cast<UActionComponent>(GetOwner()->GetComponentByClass(UActionComponent::StaticClass()));
	_statusComp = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));



	if(_statusComp && _actionComp)
	{
		//set walking speed 
		MaxWalkSpeed = _statusComp->GetFinalValue(EStatusType::EStatus_WalkingSpeed);

		_actionComp->GetActionBlackBoard()->
			GetValueChangedDelegate_Bool(EActionDataKey::EACTD_WantToSprint).AddUObject(this, &UMyCharacterMovementComponent::OnCharacterWantToSprint);
	}

	UAnimControlComponent* animControlComp = GetOwner<UAnimControlComponent>();
	if (animControlComp)
	{
		_animationViewModel = animControlComp->GetAnimationModel();
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
	if (_eventBrokerComp)
	{
		UDataInt32* eventData = NewObject<UDataInt32>(this);
		eventData->Value = MovementMode;
		_eventBrokerComp->PublishEvent(NSEventNames::MovementModeChanged, eventData);
	}
}

void UMyCharacterMovementComponent::OnCharacterWantToSprint(bool wantToSprint)
{
	if (_statusComp)
	{
		if (wantToSprint)
		{
			MaxWalkSpeed = _statusComp->GetFinalValue(EStatusType::EStatus_SprintingSpeed);
		}
		else
		{

			MaxWalkSpeed = _statusComp->GetFinalValue(EStatusType::EStatus_WalkingSpeed);
		}
	}
}
