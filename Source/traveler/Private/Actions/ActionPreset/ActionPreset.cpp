// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/ActionPreset.h"
#include "Condition/CompositeActorCondition.h"
#include "Actions/ActionBase.h"
#include "Components/ActionComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/Character.h"


void UActionPreset::VInitialize(ACharacter* character, UActionComponent* actionComp)
{
	check(character);
	check(actionComp);

	_actionComp = actionComp;

	for (TSubclassOf<UActionBase> actionClass : _arrayActionClasses)
	{
		MakeActionIns(actionClass, character, actionComp);
	}

	if (_conditionClass)
	{
		_conditionIns = NewObject<UCompositeActorCondition>(this, _conditionClass);
		_conditionIns->SetActor(_actionComp->GetOwner());
		_conditionIns->Initialize();
		_conditionIns->Subscribe(this, &UActionPreset::ActivateThisActionSet);
		_conditionIns->Validate();
	}
}

void UActionPreset::VEnter()
{
}

void UActionPreset::VLeave()
{
	AbortAllActions();
}

void UActionPreset::Tick(float deltaTime)
{
	for (auto element : _mapActionIns)
	{
		element.Value->Tick(deltaTime);
	}
}

bool UActionPreset::IsActionRunning(EActionType actionType)
{
	if (_mapActionIns.Contains(actionType))
	{
		return _mapActionIns[actionType]->GetProcessState() == EProcessState::EPS_Running;
	}
	else
	{
		return false;
	}
}

UActionBase* UActionPreset::ExecuteAction(EActionType actionType)
{
	if (_mapActionIns.Contains(actionType) == false)
	{
		return nullptr;
	}

	if (_mapActionIns[actionType]->IsAlive())
	{
		return nullptr;
	}

	_mapActionIns[actionType]->Init();
	_mapActionIns[actionType]->Execute();
	return _mapActionIns[actionType];
}

UActionBase* UActionPreset::AbortAction(EActionType actionType)
{
	if (_mapActionIns.Contains(actionType))
	{
		_mapActionIns[actionType]->Abort();
		return _mapActionIns[actionType];
	}
	else
	{
		return nullptr;
	}
}

void UActionPreset::AbortAllActions()
{
	for (auto element : _mapActionIns)
	{
		element.Value->Abort();
	}
}

void UActionPreset::MakeActionIns(TSubclassOf<UActionBase> actionClass, ACharacter* character, UActionComponent* actionComp)
{
	if (!actionClass)
	{
		return;
	}

	EActionType actionType = actionClass.GetDefaultObject()->GetActionType();
	if (_mapActionIns.Contains(actionType))
	{
		UE_LOG(LogTemp, Warning, TEXT("try to make duplicate action ins"));
		return;
	}

	UActionBase* actionIns = NewObject<UActionBase>(this, actionClass);
	actionIns->SetActionData(character, actionComp);

	_mapActionIns.Add(actionType, actionIns);
}

void UActionPreset::ActivateThisActionSet(bool result)
{
	if (_actionComp && result)
	{
		_actionComp->SwitchActionSet(this);
	}
}
