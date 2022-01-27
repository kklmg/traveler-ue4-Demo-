// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"
#include "Actions/ActionBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actions/ActionPreset/CharacterActionPreset.h"
#include "Components/PawnCameraComponent.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/MyBlueprintFunctionLibrary.h"
#include "Interface/StateInterface.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	_actionBlackBoard = NewObject<UActionBlackBoard>(this);
	
	// ...

	//Get Character
	IStateInterface* stateIntercate = GetOwner<IStateInterface>();
	if (stateIntercate == nullptr) return;
	
	OnCharacterStateChanged(stateIntercate->VGetStateData());

	//bind state changed event
	stateIntercate->VGetAnyStateChangedDelegate()->AddDynamic(this, &UActionComponent::OnCharacterStateChanged);
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_TickActionProcess(DeltaTime);
}

UActionBase* UActionComponent::ExecuteAction(EActionType actionType)
{
	if (_pCurrentActionPreset == nullptr || _mapActionProcessPool.Contains(actionType))
	{
		return nullptr;
	}

	UActionBase* action = nullptr;

	if (_pCurrentActionPreset->TryGetActionInstance(actionType, &action))
	{
		action->Abort();
		action->Initialize(this, _actionBlackBoard);
		action->VExecute();

		if (action->IsInstantAction() == false)
		{
			AddToActionProcessPool(action);
		}
	}
	return action;
}


void UActionComponent::AddToActionProcessPool(UActionBase* action)
{
	if (action == nullptr) return;

	_mapActionProcessPool.Add(action->GetActionType(), action);
}

void UActionComponent::_TickActionProcess(float deltaTime)
{
	TArray<EActionType> finieshedActionKeys;

	//find out all finished actions
	for (auto pair : _mapActionProcessPool)
	{
		if (pair.Value->IsCompleted())
		{
			finieshedActionKeys.Add(pair.Key);
		}
	}

	//remove all finished actions
	for (auto key : finieshedActionKeys)
	{
		_mapActionProcessPool.Remove(key);
	}

	//tick actions
	for (auto pair : _mapActionProcessPool)
	{
		pair.Value->VTick(deltaTime);
	}
}

UActionBlackBoard* UActionComponent::GetActionBlackBoard()
{
	return _actionBlackBoard;
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
			if (_pCurrentActionPreset != nullptr)
			{
				_pCurrentActionPreset->VLeave();
				_pCurrentActionPreset->MarkPendingKill();
			}
			_pCurrentActionPreset = actionPresetIns;
		}
	}
	_cachedStateData = newStateData;
}

void UActionComponent::ClearActionProcessPool()
{
	for (auto pair : _mapActionProcessPool)
	{
		pair.Value->Abort();
	}
	_mapActionProcessPool.Empty();
}

