// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StateComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UStateComponent::UStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ACharacter* character = GetOwner<ACharacter>();
	if(character)
	{
		character->MovementModeChangedDelegate.AddDynamic(this, &UStateComponent::OnCharacterMovementModeChanged);
	}

	
}


// Called every frame
void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FStateData UStateComponent::VGetStateData()
{
	return _stateData;
}

void UStateComponent::VSetSituationState(ESituationState newState)
{
	if (_stateData.SituationState != newState)
	{
		_stateData.SituationState = newState;
		_situationStateChangedDelegate.Broadcast(newState);
	}
}

void UStateComponent::VSetActionState(EActionState newState)
{
	if (_stateData.ActionState != newState)
	{
		_stateData.ActionState = newState;
		_actionStateChangedDelegate.Broadcast(newState);
	}
}

void UStateComponent::VSetHealthState(EHealthState newState)
{
	if (_stateData.HealthState != newState)
	{
		_stateData.HealthState = newState;
		_healthStateChangedDelegate.Broadcast(newState);
	}
}

void UStateComponent::VSetPostureState(EPostureState newState)
{
	if (_stateData.PostureState != newState)
	{
		_stateData.PostureState = newState;
		_postureStateChangedDelegate.Broadcast(newState);
	}
}

FOnSituationStateChanged* UStateComponent::VGetSituationStateChangedDelegate()
{
	return &_situationStateChangedDelegate;
}

FOnActionStateChanged* UStateComponent::VGetActionStateChangedDelegate()
{
	return &_actionStateChangedDelegate;
}

FOnHealthStateChanged* UStateComponent::VGetHealthStateChangedDelegate()
{
	return &_healthStateChangedDelegate;
}

FOnPostureStateChanged* UStateComponent::VGetPostureStateChangedDelegate()
{
	return &_postureStateChangedDelegate;
}

FOnAnyStateChanged* UStateComponent::VGetAnyStateChangedDelegate()
{
	return &_anyStateChangedDelegate;
}

void UStateComponent::OnCharacterMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	EMovementMode curMovementMode = Character->GetCharacterMovement()->MovementMode;

	switch (curMovementMode)
	{
	case MOVE_None:
		break;
	case MOVE_Walking: VSetSituationState(ESituationState::ESS_OnGround);
		break;
	case MOVE_NavWalking:
		break;
	case MOVE_Falling: VSetSituationState(ESituationState::ESS_InAir);
		break;
	case MOVE_Swimming:VSetSituationState(ESituationState::ESS_InWater);
		break;
	case MOVE_Flying: VSetSituationState(ESituationState::ESS_InAir);
		break;
	case MOVE_Custom:
		break;
	case MOVE_MAX:
		break;
	default:
		break;
	}
}
