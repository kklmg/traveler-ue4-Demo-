// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AnimControlComponent.h"
#include "Data/AnimationModelBase.h"
#include "GameFramework/Character.h"
#include "AnimNotify/AnimNotifier.h"

// Sets default values for this component's properties
UAnimControlComponent::UAnimControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;

	_animationState = EAnimationState::EAnimState_None;
}

void UAnimControlComponent::InitializeComponent()
{
	_animationModelIns = _animationModelClass ?
			NewObject<UAnimationModelBase>(this, _animationModelClass) : NewObject<UAnimationModelBase>(this);

	_character = GetOwner<ACharacter>();
}

// Called when the game starts
void UAnimControlComponent::BeginPlay()
{
	Super::BeginPlay();
}

UAnimationModelBase* UAnimControlComponent::GetAnimationModel()
{
	return _animationModelIns;
}

void UAnimControlComponent::SetAnimationState(EAnimationState newState)
{
	if (_animationState != newState)
	{
		EAnimationState prevState = _animationState;
		_animationState = newState;
		_animationStateChangedDelegate.Broadcast(prevState, _animationState);
	}
}

EAnimationState UAnimControlComponent::GetAnimationState()
{
	return _animationState;
}

FOnAnimationStateChanged& UAnimControlComponent::GetAnimationStateChangedDelegate()
{
	return _animationStateChangedDelegate;
}


// Called every frame
void UAnimControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FORCEINLINE_DEBUGGABLE UAnimInstance* UAnimControlComponent::GetAnimInstance()
{
	check(_character);
	check(_character->GetMesh());

	return _character->GetMesh()->GetAnimInstance();
}

void UAnimControlComponent::NotifyAnimStateBegin(EAnimNotifyKey notifyKey, float totalTime)
{
	if (_mapNotifiers.Contains(notifyKey))
	{
		_mapNotifiers[notifyKey]->NotifyBeginDelegate.Broadcast(totalTime);
	}
}

void UAnimControlComponent::NotifyAnimStateTick(EAnimNotifyKey notifyKey, float frameDeltaTime)
{
	if (_mapNotifiers.Contains(notifyKey))
	{
		_mapNotifiers[notifyKey]->NotifyTickDelegate.Broadcast(frameDeltaTime);
	}
}

void UAnimControlComponent::NotifyAnimStateEnd(EAnimNotifyKey notifyKey)
{
	if (_mapNotifiers.Contains(notifyKey))
	{
		_mapNotifiers[notifyKey]->NotifyEndDelegate.Broadcast();
	}
}

UAnimNotifier* UAnimControlComponent::GetNotifer(EAnimNotifyKey notifyKey)
{
	return _mapNotifiers.Contains(notifyKey) ? _mapNotifiers[notifyKey] : nullptr;
}

UAnimNotifier* UAnimControlComponent::GetOrCreateNotifer(EAnimNotifyKey notifyKey)
{
	if (_mapNotifiers.Contains(notifyKey))
	{
		return _mapNotifiers[notifyKey];
	}
	else
	{
		UAnimNotifier* notifier = NewObject<UAnimNotifier>(this);
		_mapNotifiers.Add(notifyKey, notifier);
		return notifier;
	}
}

bool UAnimControlComponent::PlayAnimMontage(EAnimMontage animMontageType)
{
	check(_character);
	if(_montageMap.Contains(animMontageType) && _montageMap[animMontageType])
	{
		if(GetAnimInstance()->Montage_IsPlaying(_montageMap[animMontageType]))
		{
			return false;
		}
		else
		{
			_character->PlayAnimMontage(_montageMap[animMontageType]);
			return true;
		}
	}
	else
	{
		return false;
	}
}
