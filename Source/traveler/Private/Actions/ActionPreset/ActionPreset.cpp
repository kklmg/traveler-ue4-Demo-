// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/ActionPreset.h"
#include "Actions/ActionBase.h"


void UActionPreset::VEnter()
{

}
void UActionPreset::VLeave()
{
	_mapActionInstaces.Empty();
}

bool UActionPreset::TryMakeActionInstance(EActionType actionType, UActionBase** outActionInstance)
{
	//try find action instance and return
	if (_mapActionInstaces.Contains(actionType))
	{
		*outActionInstance = _mapActionInstaces[actionType];
		return true;
	}

	//try make instance of the action and return
	else
	{
		UActionBase* actionInstance = MakeActionInstance(actionType);

		if (actionInstance)
		{
			*outActionInstance = actionInstance;
			return true;
		}
	}

	return false;
}

bool UActionPreset::TryGetActionClass(EActionType actionType, TSubclassOf<UActionBase> outActionClass)
{
	for (auto actionClass : _arrayActionClasses)
	{
		if (actionClass.GetDefaultObject()->GetActionType() == actionType)
		{
			outActionClass = actionClass;
			return true;
		}
	}
	return false;
}

UActionBase* UActionPreset::MakeActionInstance(EActionType actionType)
{
	for (TSubclassOf<UActionBase> actionClass : _arrayActionClasses)
	{
		if (actionClass == nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("exist empty actionclass in action preset"))
			continue;
		}

		if (actionClass.GetDefaultObject()->GetActionType() == actionType)
		{
			UActionBase* action = NewObject<UActionBase>(this, actionClass);
			if (action != nullptr)
			{
				_mapActionInstaces.Add(action->GetActionType(), action);
				return action;
			}
			UE_LOG(LogTemp, Warning, TEXT("Make instance of UAction Failed!"));
			return nullptr;
		}
	}
	return nullptr;
}

void UActionPreset::MakeAllActionInstances()
{
	for (auto actionClass : _arrayActionClasses)
	{
		if (_mapActionInstaces.Contains(actionClass.GetDefaultObject()->GetActionType()) == false)
		{
			static UActionBase* action = NewObject<UActionBase>(this, actionClass);

			if (action == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Make instance of UActionBase Failed!"));
				continue;
			}

			_mapActionInstaces.Add(action->GetActionType(), action);
		}
	}
}

void UActionPreset::AddActionClass(TSubclassOf<UActionBase> actionClass)
{
	if (actionClass)
	{
		_arrayActionClasses.Add(actionClass);
	}
}


