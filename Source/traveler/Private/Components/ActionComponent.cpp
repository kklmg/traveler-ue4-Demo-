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

	if(_defaultActionPresetGroupClass)
	{
		_curActionPresetGroup = NewObject<UActionPresetGroup>(this,_defaultActionPresetGroupClass);
		check(_curActionPresetGroup)
		_curActionPresetGroup->Init(_character, this);
		_mapActionPresetGroup.Add(EActionPrestGroup::EACTPresetGroup_BasicActions, _curActionPresetGroup);
	}
}

// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (_eventBrokerComp)
	{
		_eventBrokerComp->SubscribeEvent(NSEvent::ActorLifeStateChanged::Name,this, &UActionComponent::OnReceiveEvent_LifeStateChanged);
	}
}

void UActionComponent::OnReceiveEvent_LifeStateChanged(UObject* baseData)
{
	auto eventData = Cast<NSEvent::ActorLifeStateChanged::DataType>(baseData);
	if (!eventData) return;
	if (_bActorAlive == eventData->Value) return;

	_bActorAlive = eventData->Value;
	if(_bActorAlive == false)
	{
		AbortAllActions();
	}
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(_curActionPresetGroup)
	{
		_curActionPresetGroup->Tick(DeltaTime);
	}
}

void UActionComponent::ExecuteAction(EActionType actionType)
{
	if (_bActorAlive == false || _curActionPresetGroup == nullptr)
	{
		return;
	}
	_curActionPresetGroup->ExecuteAction(actionType);
}

void UActionComponent::AbortAction(EActionType actionType)
{
	return _curActionPresetGroup ? _curActionPresetGroup->AbortAction(actionType) : nullptr;
}

UActionBlackBoard* UActionComponent::GetActionBlackBoard()
{
	return _actionBlackBoard;
}

void UActionComponent::SwitchActionPresetGroup(EActionPrestGroup presetGroupType)
{
	if (_mapActionPresetGroup.Contains(presetGroupType)) 
	{	
		if(_curActionPresetGroup)
		{
			_curActionPresetGroup->AbortAllActions();
		}
		_curActionPresetGroup = _mapActionPresetGroup[presetGroupType];
	}
}

void UActionComponent::AbortAllActions()
{
	if (_curActionPresetGroup) 
	{
		_curActionPresetGroup->AbortAllActions();
	}
}

bool UActionComponent::IsActionAlive(EActionType actionType)
{
	return _curActionPresetGroup ? _curActionPresetGroup->IsActionAlive(actionType) : false;
}

EProcessState UActionComponent::GetActionState(EActionType actionType)
{
	return  _curActionPresetGroup ?
		_curActionPresetGroup->GetActionState(actionType) : EProcessState::EPS_None;
}



