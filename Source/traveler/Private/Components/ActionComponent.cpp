// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"
#include "Actions/ActionBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actions/ActionPreset/CharacterActionPreset.h"
#include "Components/PawnCameraComponent.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/MyGameplayStatics.h"
#include "Interface/StateInterface.h"
#include "Interface/EventBrokerInterface.h"
#include "Actions/ActionPreset/ActionPresetTrigger.h"


// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
	bWantsInitializeComponent = true;
}


void UActionComponent::InitializeComponent()
{
	Super::InitializeComponent();

	_actionBlackBoard = NewObject<UActionBlackBoard>(this);
	_mapActionProcessPool.SetNum(int32(EActionType::EACT_Max),false);
}

// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	_eventBrokerInterface = GetOwner<IEventBrokerInterface>();

	IStateInterface* stateIntercate = GetOwner<IStateInterface>();
	if (stateIntercate == nullptr) return;
	
	//OnCharacterStateChanged(stateIntercate->VGetStateData());

	//bind state changed event
	//stateIntercate->VGetAnyStateChangedDelegate()->AddDynamic(this, &UActionComponent::OnCharacterStateChanged);
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_TickActionProcess(DeltaTime);
}

UActionBase* UActionComponent::ExecuteAction(EActionType actionType)
{
	if (_curActionSet == nullptr)
	{
		return nullptr;
	}


	int32 index = int32(actionType);

	//the same action is in progress 
	if(_mapActionProcessPool[index] &&
		_mapActionProcessPool[index]->GetActionProcessState() == EProcessState::EPS_Running)
	{
		return nullptr;
	}


	if (_curActionSet->TryMakeActionInstance(actionType, &_mapActionProcessPool[index]))
	{
		_mapActionProcessPool[index]->Initialize(this, _actionBlackBoard);
		_mapActionProcessPool[index]->Execute();
	}
	return _mapActionProcessPool[index];
}


void UActionComponent::_TickActionProcess(float deltaTime)
{
	TArray<EActionType> finieshedActionKeys;

	for (int32 i = 0; i < _mapActionProcessPool.Num(); ++i)
	{
		if (_mapActionProcessPool[i])
		{
			if(_mapActionProcessPool[i]->IsCompleted())
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

IEventBrokerInterface* UActionComponent::GetEventBrokerInterface()
{
	return _eventBrokerInterface;
}

void UActionComponent::OnCharacterStateChanged(FStateData newStateData)
{
	if (_cachedStateData.MovementMode != newStateData.MovementMode)
	{
		//preset 
		if (_mapActionPreset.Contains(newStateData.MovementMode))
		{
			//clear process pool
			ClearActionProcessPool();

			//Make instance of ActionPresetClass
			TSubclassOf<UCharacterActionPreset> actionpresetClass = _mapActionPreset[newStateData.MovementMode];

			UCharacterActionPreset* actionPresetIns = actionpresetClass ?
				NewObject<UCharacterActionPreset>(this, actionpresetClass)
				: NewObject<UCharacterActionPreset>(this);

			actionPresetIns->VEnter();

			//Set Current Action set
			if (_curActionSet != nullptr)
			{
				_curActionSet->VLeave();
				_curActionSet->MarkPendingKill();
			}
			_curActionSet = actionPresetIns;
		}
	}
	_cachedStateData = newStateData;
}

void UActionComponent::SwitchActionSet(UCharacterActionPreset* actionSet)
{
	if (_curActionSet == actionSet) return;

	_curActionSet->VLeave();
	_curActionSet = actionSet;
	_curActionSet->VEnter();
}

void UActionComponent::ClearActionProcessPool()
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
			&& _mapActionProcessPool[index]->GetActionProcessState() == EProcessState::EPS_Running;
}



