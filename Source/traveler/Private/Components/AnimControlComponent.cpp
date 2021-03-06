// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AnimControlComponent.h"
#include "Data/AnimationModelBase.h"
#include "GameFramework/Character.h"
#include "AnimNotify/AnimNotifier.h"
#include "Components/EventBrokerComponent.h"
#include "Event/EventData.h"

// Sets default values for this component's properties
UAnimControlComponent::UAnimControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;

	_animationState = EAnimationState::EAnimState_None;
	_animationModelClass = UAnimationModelBase::StaticClass();
}

void UAnimControlComponent::InitializeComponent()
{
	_animViewModelIns = NewObject<UAnimationModelBase>(this, _animationModelClass);
	check(_animViewModelIns)

	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));
	if (_eventBrokerComp)
	{
		_eventBrokerComp->SubscribeEvent<UAnimControlComponent>
			(NSEventData::ActorLifeStateChanged::Name, this, &UAnimControlComponent::OnReceiveEvent_ActorLifeStateChanged);
	}

	_character = GetOwner<ACharacter>();
}

// Called when the game starts
void UAnimControlComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UAnimControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UAnimationModelBase* UAnimControlComponent::GetAnimViewModel()
{
	return _animViewModelIns;
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

FORCEINLINE_DEBUGGABLE UAnimInstance* UAnimControlComponent::GetAnimInstance()
{
	check(_character);
	check(_character->GetMesh());

	return _character->GetMesh()->GetAnimInstance();
}

void UAnimControlComponent::NotifyAnimStateBegin(EAnimNotifyKeyType notifyKey, float totalTime)
{
	if (_mapNotifiers.Contains(notifyKey))
	{
		_mapNotifiers[notifyKey]->NotifyBeginDelegate.Broadcast(totalTime);
	}
}

void UAnimControlComponent::NotifyAnimStateTick(EAnimNotifyKeyType notifyKey, float frameDeltaTime)
{
	if (_mapNotifiers.Contains(notifyKey))
	{
		_mapNotifiers[notifyKey]->NotifyTickDelegate.Broadcast(frameDeltaTime);
	}
}

void UAnimControlComponent::NotifyAnimStateEnd(EAnimNotifyKeyType notifyKey)
{
	if (_mapNotifiers.Contains(notifyKey))
	{
		_mapNotifiers[notifyKey]->NotifyEndDelegate.Broadcast();
	}
}

UAnimNotifier* UAnimControlComponent::GetNotifer(EAnimNotifyKeyType notifyKey)
{
	return _mapNotifiers.Contains(notifyKey) ? _mapNotifiers[notifyKey] : nullptr;
}

UAnimNotifier* UAnimControlComponent::GetOrCreateNotifer(EAnimNotifyKeyType notifyKey)
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

bool UAnimControlComponent::PlayAnimMontage(EAnimMontageKey animMontageType)
{
	check(_character);
	if(_montageMap.Contains(animMontageType) && _montageMap[animMontageType])
	{
		if(GetAnimInstance()->Montage_IsPlaying(_montageMap[animMontageType]))
		{
			return false;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("montage is playing"));
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

bool UAnimControlComponent::StopAnimMontage(EAnimMontageKey animMontageType)
{
	check(_character);
	if (_montageMap.Contains(animMontageType) && _montageMap[animMontageType])
	{
		_character->StopAnimMontage(_montageMap[animMontageType]);
		return true;
	}
	else
	{
		return false;
	}
}

bool UAnimControlComponent::ContainsAnimMontage(EAnimMontageKey animMontageType)
{
	return _montageMap.Contains(animMontageType);
}

void UAnimControlComponent::OnReceiveEvent_ActorLifeStateChanged(UObject* baseData)
{
	auto eventData = Cast<NSEventData::ActorLifeStateChanged::Type>(baseData);
	if (eventData)
	{
		_animViewModelIns->SetBool(NSAnimationDataKey::bIsAlive, eventData->Value);
	}
}