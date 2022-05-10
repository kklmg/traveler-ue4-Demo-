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
		_eventBrokerComp->SubscribeEvent(NSEvent::ActorLifeStateChanged::Name, this, &UActionComponent::OnReceiveEvent_LifeStateChanged);
	}

	if (_defaultActionPresetGroupClass)
	{
		UActionPresetGroup* defaultActionPresetGroup = NewObject<UActionPresetGroup>(this, _defaultActionPresetGroupClass);
		check(defaultActionPresetGroup)
			defaultActionPresetGroup->Init(_character, this, _character->GetCharacterMovement()->MovementMode);
		_mapActionPresetGroup.Add(EActionPrestGroup::EACTPresetGroup_BasicActions, defaultActionPresetGroup);
		_curActionPrestGroupType = EActionPrestGroup::EACTPresetGroup_BasicActions;
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
	auto eventData = Cast<NSEvent::ActorLifeStateChanged::DataType>(baseData);
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

FORCEINLINE_DEBUGGABLE UActionBlackBoard* UActionComponent::GetActionBlackBoard()
{
	return _actionBlackBoard;
}

FORCEINLINE_DEBUGGABLE UActionPresetGroup* UActionComponent::GetCurActionPresetGroup()
{
	return _mapActionPresetGroup.Contains(_curActionPrestGroupType) ?
		_mapActionPresetGroup[_curActionPrestGroupType] : nullptr;
}

void UActionComponent::AbortAllActions()
{
	if (GetCurActionPresetGroup())
	{
		GetCurActionPresetGroup()->AbortAllActions();
	}
}

void UActionComponent::RegisterActionPresetGroup(EActionPrestGroup presetGroupType, TSubclassOf<UActionPresetGroup> actionPresetGroupClass)
{
	if (!actionPresetGroupClass) return;

	if (_curActionPrestGroupType == presetGroupType && GetCurActionPresetGroup())
	{
		GetCurActionPresetGroup()->AbortAllActions();
	}

	//make instance
	UActionPresetGroup* newActionPresetGroup = NewObject<UActionPresetGroup>(this, actionPresetGroupClass);
	newActionPresetGroup->Init(_character, this, _character->GetCharacterMovement()->MovementMode);

	if (_mapActionPresetGroup.Contains(presetGroupType))
	{
		_mapActionPresetGroup[presetGroupType] = newActionPresetGroup;
	}
	else
	{
		_mapActionPresetGroup.Add(presetGroupType, newActionPresetGroup);
	}
}

void UActionComponent::SwitchActionPresetGroup(EActionPrestGroup presetGroupType)
{
	if (_curActionPrestGroupType == presetGroupType) return;
	if (_mapActionPresetGroup.Contains(presetGroupType))
	{
		if (GetCurActionPresetGroup())
		{
			GetCurActionPresetGroup()->AbortAllActions();
		}

		_curActionPrestGroupType = presetGroupType;
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
