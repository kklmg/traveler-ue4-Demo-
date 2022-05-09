// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/ActionPresetGroup.h"
#include "Actions/ActionPreset/ActionPreset.h"
#include "Components/ActionComponent.h"
#include "GameSystem/DebugMessageHelper.h"



void UActionPresetGroup::Init(ACharacter* character, UActionComponent* actionComp)
{
	for (auto presetClass : _actionPresetClasses)
	{
		if (presetClass)
		{
			auto actionPreset = NewObject<UActionPreset>(this, presetClass);
			actionPreset->VInitialize(character, actionComp, this);
			_actionPresetInstances.Add(actionPreset);
		}
	}
}

void UActionPresetGroup::Tick(float deltaTime)
{
	if (_curActionSet)
	{
		_curActionSet->Tick(deltaTime);
	}
}

bool UActionPresetGroup::IsActionAlive(EActionType actionType)
{
	return _curActionSet ? _curActionSet->IsActionAlive(actionType) : false;
}

EProcessState UActionPresetGroup::GetActionState(EActionType actionType)
{
	return  _curActionSet ?
		_curActionSet->GetActionState(actionType) : EProcessState::EPS_None;
}

void UActionPresetGroup::ExecuteAction(EActionType actionType)
{
	if (_curActionSet)
	{
	 _curActionSet->ExecuteAction(actionType);
	 }
}

void UActionPresetGroup::AbortAction(EActionType actionType)
{
	if (_curActionSet)
	{
		_curActionSet->AbortAction(actionType);
	}
}

void UActionPresetGroup::AbortAllActions()
{
	if (_curActionSet)
	{
		_curActionSet->AbortAllActions();
	}
}

void UActionPresetGroup::SwitchActionSet(UActionPreset* actionSet)
{
	if (_curActionSet == actionSet) return;

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

