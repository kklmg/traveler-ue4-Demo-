// Fill out your copyright notice in the Description page of Project Settings.


#include "State/State.h"

void UState::VEnter()
{

}
void UState::VLeave() 
{
	_mapActionInstaces.Empty();
}

bool UState::TryGetActionInstance(FName actionName, UAction** outActionInstance)
{
	//try find action instance and return
	if (_mapActionInstaces.Contains(actionName))
	{
		*outActionInstance = _mapActionInstaces[actionName];
		return true;
	}

	//try make instance of the action and return
	else
	{
		UAction* actionInstance = MakeActionInstance(actionName);

		if (actionInstance)
		{
			*outActionInstance = actionInstance;
			return true;
		}
	}

	return false;
}

bool UState::TryGetActionClass(FName actionName, TSubclassOf<UAction> outActionClass)
{
	for (auto actionClass : _arrayActionClasses)
	{
		if (actionClass.GetDefaultObject()->GetActionName() == actionName) 
		{
			outActionClass = actionClass;
			return true;
		}
	}
	return false;
}

UAction* UState::MakeActionInstance(FName actionName)
{
	for (auto actionClass : _arrayActionClasses)
	{
		if (actionClass.GetDefaultObject()->GetActionName() == actionName)
		{
			UAction* action = NewObject<UAction>(this,actionClass);
			if (action != nullptr)
			{
				_mapActionInstaces.Add(action->GetActionName(), action);
				return action;
			}
			UE_LOG(LogTemp, Warning, TEXT("Make instance of UAction Failed!"));
			return nullptr;
		}
	}
	return nullptr;
}

void UState::MakeAllActionInstances() 
{
	for (auto actionClass : _arrayActionClasses)
	{
		if (_mapActionInstaces.Contains(actionClass.GetDefaultObject()->GetActionName()) == false)
		{
			static UAction* action = NewObject<UAction>(this, actionClass);
		
			if (action == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Make instance of UAction Failed!"));
				continue;
			}

			_mapActionInstaces.Add(action->GetActionName(), action);
		}
	}
}

void UState::AddActionClass(TSubclassOf<UAction> actionClass)
{
	if (actionClass) 
	{
		_arrayActionClasses.Add(actionClass);
	}
}

EMovementMode UState::GetMovementMode() 
{
	return _movementMode;
}