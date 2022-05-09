// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/ActionPreset.h"
#include "Actions/ActionPreset/ActionPresetGroup.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actions/ActionBase.h"
#include "Condition/CompositeActorCondition.h"
#include "Components/ActionComponent.h"
#include "GameFramework/Character.h"


void UActionPreset::VInitialize(ACharacter* character, UActionComponent* actionComp, UActionPresetGroup* actionPresetGroup)
{
	check(character);
	check(actionComp);

	_actionPresetGroup = actionPresetGroup;

	for (TSubclassOf<UActionBase> actionClass : _arrayActionClasses)
	{
		MakeActionIns(actionClass, character, actionComp);
	}

	if (_conditionClass)
	{
		_conditionIns = NewObject<UCompositeActorCondition>(this, _conditionClass);
		_conditionIns->SetActor(actionComp->GetOwner());
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

bool UActionPreset::IsActionAlive(EActionType actionType)
{
	return _mapActionIns.Contains(actionType) ?
		_mapActionIns[actionType]->IsAlive() : false;
}

EProcessState UActionPreset::GetActionState(EActionType actionType)
{
	return  _mapActionIns.Contains(actionType) ?
		_mapActionIns[actionType]->GetProcessState() : EProcessState::EPS_None;
}

void UActionPreset::ExecuteAction(EActionType actionType)
{
	if (_mapActionIns.Contains(actionType) && _mapActionIns[actionType]->IsAlive() == false)
	{
		_mapActionIns[actionType]->Init();
		_mapActionIns[actionType]->Execute();
	}
}

void UActionPreset::AbortAction(EActionType actionType)
{
	if (_mapActionIns.Contains(actionType))
	{
		_mapActionIns[actionType]->Abort();
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
	actionIns->SetUpActionData(character, actionComp);

	_mapActionIns.Add(actionType, actionIns);
}

void UActionPreset::ActivateThisActionSet(bool result)
{
	if (_actionPresetGroup && result)
	{
		_actionPresetGroup->SwitchActionSet(this);
	}
}
