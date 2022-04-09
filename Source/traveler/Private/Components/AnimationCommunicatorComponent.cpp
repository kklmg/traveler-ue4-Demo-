// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AnimationCommunicatorComponent.h"
#include "Data/AnimationModelBase.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UAnimationCommunicatorComponent::UAnimationCommunicatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;

	_animationState = EAnimationState::EAnimState_Walk;
}

void UAnimationCommunicatorComponent::InitializeComponent()
{
	_animationModelIns = _animationModelClass ?
			NewObject<UAnimationModelBase>(this, _animationModelClass) : NewObject<UAnimationModelBase>(this);

	_character = GetOwner<ACharacter>();
}

// Called when the game starts
void UAnimationCommunicatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_character->PlayAnimMontage(_montage);
}

UAnimationModelBase* UAnimationCommunicatorComponent::GetAnimationModel()
{
	return _animationModelIns;
}

void UAnimationCommunicatorComponent::SetAnimationState(EAnimationState newState)
{
	if (_animationState != newState)
	{
		EAnimationState prevState = _animationState;
		_animationState = newState;
		_animationStateChangedDelegate.Broadcast(prevState, _animationState);
	}
}

EAnimationState UAnimationCommunicatorComponent::GetAnimationState()
{
	return _animationState;
}

FOnAnimationStateChanged& UAnimationCommunicatorComponent::GetAnimationStateChangedDelegate()
{
	return _animationStateChangedDelegate;
}


// Called every frame
void UAnimationCommunicatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}