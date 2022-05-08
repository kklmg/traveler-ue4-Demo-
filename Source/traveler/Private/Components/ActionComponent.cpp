// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"
#include "Actions/ActionBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actions/ActionPreset/CharacterActionPreset.h"
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

	for (auto presetClass : _actionPresetClasses)
	{
		if (presetClass)
		{
			auto actionPreset = NewObject<UActionPreset>(this, presetClass);
			actionPreset->VInitialize(_character, this);
			_actionPresetInstances.Add(actionPreset);
		}
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
	if(_curActionSet)
	{
		_curActionSet->Tick(DeltaTime);
	}
}

UActionBase* UActionComponent::ExecuteAction(EActionType actionType)
{
	if (_bActorAlive == false || _curActionSet == nullptr)
	{
		return nullptr;
	}
	return _curActionSet->ExecuteAction(actionType);
}

UActionBase* UActionComponent::AbortAction(EActionType actionType)
{
	return _curActionSet ? _curActionSet->AbortAction(actionType) : nullptr;
}

UActionBlackBoard* UActionComponent::GetActionBlackBoard()
{
	return _actionBlackBoard;
}

void UActionComponent::SwitchActionSet(UActionPreset* actionSet)
{
	if (_curActionSet == actionSet) return;

	if(_curActionSet)
	{
		_curActionSet->VLeave();
	}
	
	_curActionSet = actionSet;

	if (_curActionSet)
	{
		_curActionSet->VEnter();
	}

	UDebugMessageHelper::Messsage_String(TEXT("ActionComp"), TEXT("ActionSetChanged"));
}

void UActionComponent::AbortAllActions()
{
	if (_curActionSet) 
	{
		_curActionSet->AbortAllActions();
	}
}

bool UActionComponent::IsActionRunning(EActionType actionType)
{
	return _curActionSet ? _curActionSet->IsActionRunning(actionType) : false;
}



