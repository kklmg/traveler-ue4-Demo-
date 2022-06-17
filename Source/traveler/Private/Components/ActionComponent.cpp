// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"
#include "Actions/ActionBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actions/ActionPreset/ActionPresetGroup.h"
#include "Components/PawnCameraComponent.h"
#include "Components/EventBrokerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/MyGameplayStatics.h"
#include "GameSystem/DebugMessageHelper.h"
#include "Data/MyDelegates.h"
#include "GameFramework/Character.h"



// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;
	_bActorAlive = true;

	_basicActionPresetGroupClass = UActionPresetGroup::StaticClass();
}


void UActionComponent::InitializeComponent()
{
	Super::InitializeComponent();

	_character = GetOwner<ACharacter>();
	check(_character);

	_actionBlackBoard = NewObject<UActionBlackBoard>(this);
	check(_actionBlackBoard);

	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (_eventBrokerComp)
	{
		_eventBrokerComp->SubscribeEvent(NSEventData::ActorLifeStateChanged::Name, this, &UActionComponent::OnReceiveEvent_LifeStateChanged);
	}

	if (_basicActionPresetGroupClass)
	{
		_basicActionPresetGroupIns = NewObject<UActionPresetGroup>(this, _basicActionPresetGroupClass);
		check(_basicActionPresetGroupIns)
		_basicActionPresetGroupIns->Init(_character, this, _character->GetCharacterMovement()->MovementMode);
	}

	//
	_character->MovementModeChangedDelegate.AddDynamic(this, &UActionComponent::OnMovementModeChanged);
}

void UActionComponent::OnMovementModeChanged(ACharacter* character, EMovementMode prevMovementMode, uint8 previousCustomMode)
{
	if (GetCurActionPresetGroup())
	{
		GetCurActionPresetGroup()->SwitchActionPreset(character->GetCharacterMovement()->MovementMode);
	}
}

void UActionComponent::OnReceiveEvent_LifeStateChanged(UObject* baseData)
{
	auto eventData = Cast<NSEventData::ActorLifeStateChanged::Type>(baseData);
	if (!eventData) return;
	if (_bActorAlive == eventData->Value) return;

	_bActorAlive = eventData->Value;
	if (_bActorAlive == false)
	{
		AbortAllActions();
	}
}

// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetCurActionPresetGroup())
	{
		GetCurActionPresetGroup()->Tick(DeltaTime);
	}
}

void UActionComponent::ExecuteAction(EActionType actionType)
{
	if (_bActorAlive == false || GetCurActionPresetGroup() == nullptr)
	{
		return;
	}
	GetCurActionPresetGroup()->ExecuteAction(actionType);
}

void UActionComponent::AbortAction(EActionType actionType)
{
	return GetCurActionPresetGroup() ? GetCurActionPresetGroup()->AbortAction(actionType) : nullptr;
}

UActionBlackBoard* UActionComponent::GetActionBlackBoard()
{
	return _actionBlackBoard;
}

UActionPresetGroup* UActionComponent::GetCurActionPresetGroup()
{
	return _bActionPresetGroupOverrided ? _overridedActionPresetGroupIns : _basicActionPresetGroupIns;
}

void UActionComponent::AbortAllActions()
{
	if (GetCurActionPresetGroup())
	{
		GetCurActionPresetGroup()->AbortAllActions();
	}
}

bool UActionComponent::OverrideActionPresetGroup(TSubclassOf<UActionPresetGroup> actionPresetGroupClass)
{
	if (_bActionPresetGroupOverrided == true || actionPresetGroupClass == nullptr) return false;

	//make instance
	_overridedActionPresetGroupIns = NewObject<UActionPresetGroup>(this, actionPresetGroupClass);
	_overridedActionPresetGroupIns->Init(_character, this, _character->GetCharacterMovement()->MovementMode);

	_basicActionPresetGroupIns->AbortAllActions();

	_bActionPresetGroupOverrided = true;
	return true;
}

void UActionComponent::ClearOverridedActionPresetGroup()
{
	if (_bActionPresetGroupOverrided)
	{
		_overridedActionPresetGroupIns->AbortAllActions();
		_bActionPresetGroupOverrided = false;
	}
}

bool UActionComponent::IsActionAlive(EActionType actionType)
{
	return GetCurActionPresetGroup() ? GetCurActionPresetGroup()->IsActionAlive(actionType) : false;
}

EProcessState UActionComponent::GetActionState(EActionType actionType)
{
	return  GetCurActionPresetGroup() ?
		GetCurActionPresetGroup()->GetActionState(actionType) : EProcessState::EPS_None;
}
