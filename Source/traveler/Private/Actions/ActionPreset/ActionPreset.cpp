// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/ActionPreset.h"
#include "Actions/ActionBase.h"

void UActionPreset::VInitialize()
{
	for (TSubclassOf<UActionBase> actionClass : _arrayActionClasses)
	{
		AddActionClassToMap(actionClass);
	}
}

void UActionPreset::VEnter()
{
}

void UActionPreset::VLeave()
{
}

UActionBase* UActionPreset::GetActionInstance(EActionType actionType)
{
	if (_mapActionClasses.Contains(actionType))
	{
		UActionBase* actionIns = NewObject<UActionBase>(this, _mapActionClasses[actionType]);
		return actionIns;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("no matching action class"));
		return nullptr;
	}
}

void UActionPreset::AddActionClassToMap(TSubclassOf<UActionBase> actionClass)
{
	if (!actionClass) return;
	EActionType actionType = actionClass.GetDefaultObject()->GetActionType();

	if (_mapActionClasses.Contains(actionType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Duplicated action classes in action preset!"));
	}
	else
	{
		_mapActionClasses.Add(actionType, actionClass);
	}
}


