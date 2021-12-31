// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionSet.h"
#include "Actions/Action.h"


void UActionSet::VEnter()
{

}
void UActionSet::VLeave()
{
	_mapActionInstaces.Empty();
}

bool UActionSet::TryGetActionInstance(EActionType actionType, UAction** outActionInstance)
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
		UAction* actionInstance = MakeActionInstance(actionType);

		if (actionInstance)
		{
			*outActionInstance = actionInstance;
			return true;
		}
	}

	return false;
}

bool UActionSet::TryGetActionClass(EActionType actionType, TSubclassOf<UAction> outActionClass)
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

UAction* UActionSet::MakeActionInstance(EActionType actionType)
{
	for (auto actionClass : _arrayActionClasses)
	{
		if (actionClass.GetDefaultObject()->GetActionType() == actionType)
		{
			UAction* action = NewObject<UAction>(this, actionClass);
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

void UActionSet::MakeAllActionInstances()
{
	for (auto actionClass : _arrayActionClasses)
	{
		if (_mapActionInstaces.Contains(actionClass.GetDefaultObject()->GetActionType()) == false)
		{
			static UAction* action = NewObject<UAction>(this, actionClass);

			if (action == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Make instance of UAction Failed!"));
				continue;
			}

			_mapActionInstaces.Add(action->GetActionType(), action);
		}
	}
}

void UActionSet::AddActionClass(TSubclassOf<UAction> actionClass)
{
	if (actionClass)
	{
		_arrayActionClasses.Add(actionClass);
	}
}


