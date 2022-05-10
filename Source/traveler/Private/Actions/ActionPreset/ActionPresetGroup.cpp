// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/ActionPresetGroup.h"
#include "Actions/ActionPreset/ActionPreset.h"
#include "Components/ActionComponent.h"
#include "GameSystem/DebugMessageHelper.h"



void UActionPresetGroup::Init(ACharacter* character, UActionComponent* actionComp, EMovementMode movementMode)
{
	_movementMode = movementMode;
	for (auto Element : _mapActionPresetClass)
	{
		if (Element.Value)
		{
			auto actionPreset = NewObject<UActionPreset>(this, Element.Value);
			actionPreset->VInitialize(character, actionComp);
			_mapActionPresetIns.Add(Element.Key, actionPreset);
		}
	}
}

void UActionPresetGroup::Tick(float deltaTime)
{
	if (GetCurActionPreset())
	{
		GetCurActionPreset()->Tick(deltaTime);
	}
}

bool UActionPresetGroup::IsActionAlive(EActionType actionType)
{
	return GetCurActionPreset() ? GetCurActionPreset()->IsActionAlive(actionType) : false;
}

EProcessState UActionPresetGroup::GetActionState(EActionType actionType)
{
	return  GetCurActionPreset() ?
		GetCurActionPreset()->GetActionState(actionType) : EProcessState::EPS_None;
}

void UActionPresetGroup::ExecuteAction(EActionType actionType)
{
	if (GetCurActionPreset())
	{
		GetCurActionPreset()->ExecuteAction(actionType);
	}
}

void UActionPresetGroup::AbortAction(EActionType actionType)
{
	if (GetCurActionPreset())
	{
		GetCurActionPreset()->AbortAction(actionType);
	}
}

void UActionPresetGroup::AbortAllActions()
{
	if (GetCurActionPreset())
	{
		GetCurActionPreset()->AbortAllActions();
	}
}

void UActionPresetGroup::SwitchActionPreset(EMovementMode movementMode)
{
	if (_movementMode != movementMode)
	{
		if(_mapActionPresetIns.Contains(_movementMode))
		{
			_mapActionPresetIns[_movementMode]->VLeave();
		}
	
		_movementMode = movementMode;

		if (_mapActionPresetIns.Contains(_movementMode))
		{
			_mapActionPresetIns[_movementMode]->VEnter();
		}
	}
}

FORCEINLINE_DEBUGGABLE UActionPreset* UActionPresetGroup::GetCurActionPreset()
{
	return _mapActionPresetIns.Contains(_movementMode) ? _mapActionPresetIns[_movementMode] : nullptr;
}

