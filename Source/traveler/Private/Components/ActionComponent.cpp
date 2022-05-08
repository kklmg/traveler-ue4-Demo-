// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"
#include "Actions/ActionBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actions/ActionPreset/CharacterActionPreset.h"
#include "Components/PawnCameraComponent.h"
#include "Components/EventBrokerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/MyGameplayStatics.h"
#include "Actions/ActionPreset/ActionPresetTrigger.h"
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

	_mapActionProcessPool.SetNum(int32(EActionType::EACT_Max), false);
	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));

	for (auto triggerClass : _actionSetTriggerClasses)
	{
		if (triggerClass)
		{
			UActionPresetTrigger* trigger = NewObject<UActionPresetTrigger>(this, triggerClass);
			trigger->Initiazlie(this);
			_actionSetTriggerInstances.Add(trigger);
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
		AbortAllProcesses();
	}
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_tickActionProcess(DeltaTime);
}

UActionBase* UActionComponent::ExecuteAction(EActionType actionType)
{
	if (_bActorAlive == false || _curActionSet == nullptr)
	{
		return nullptr;
	}

	//array index(pool slot)
	int32 index = int32(actionType);

	if (index >= _mapActionProcessPool.Num())
	{
		return nullptr;
	}

	//Handle case when the same action is in progress 
	if (_mapActionProcessPool[index] &&
		_mapActionProcessPool[index]->GetProcessState() == EProcessState::EPS_Running)
	{
		//todo
		return nullptr;
	}

	//make and get Action Instance
	UActionBase* newActionIns = _curActionSet->GetActionInstance(actionType);
	if (newActionIns)
	{
		//Execute Action
		newActionIns->SetActionData(_character, this, _actionBlackBoard);
		newActionIns->Init();
		newActionIns->Execute();

		//add action Instance to pool for management
		_mapActionProcessPool[index] = newActionIns;
	}

	return newActionIns;
}

UActionBase* UActionComponent::AbortAction(EActionType actionType)
{
	int32 index = int32(actionType);

	if (index >= _mapActionProcessPool.Num())
	{
		return nullptr;
	}

	if(_mapActionProcessPool[index])
	{
		UActionBase* cachedAction = _mapActionProcessPool[index];
		_mapActionProcessPool[index]->Abort();
		_mapActionProcessPool[index] = nullptr;

		return cachedAction;
	}

	return nullptr;
}


void UActionComponent::_tickActionProcess(float deltaTime)
{
	TArray<EActionType> finieshedActionKeys;

	for (int32 i = 0; i < _mapActionProcessPool.Num(); ++i)
	{
		if (_mapActionProcessPool[i])
		{
			if (_mapActionProcessPool[i]->IsDead())
			{
				_mapActionProcessPool[i] = nullptr;
			}
			else
			{
				_mapActionProcessPool[i]->Tick(deltaTime);
			}
		}
	}
}

UActionBlackBoard* UActionComponent::GetActionBlackBoard()
{
	return _actionBlackBoard;
}

void UActionComponent::SwitchActionSet(UCharacterActionPreset* actionSet)
{
	if (_curActionSet == actionSet) return;

	AbortAllProcesses();
	if (_curActionSet)
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

void UActionComponent::AbortAllProcesses()
{
	for (int32 i = 0; i < _mapActionProcessPool.Num(); ++i)
	{
		if (_mapActionProcessPool[i])
		{
			_mapActionProcessPool[i]->Abort();
			_mapActionProcessPool[i] = nullptr;
		}
	}
}

bool UActionComponent::CheckActionIsInProgress(EActionType actionType)
{
	int32 index = int32(actionType);
	return _mapActionProcessPool[index]
		&& _mapActionProcessPool[index]->GetProcessState() == EProcessState::EPS_Running;
}



