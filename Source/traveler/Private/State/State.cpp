// Fill out your copyright notice in the Description page of Project Settings.


#include "State/State.h"

void UState::Enter()
{

}
void UState::Leave() 
{
	_mapActionInstaces.Empty();
}

bool UState::TryGetActionInstance(FName actionName, UAction** outActionInstance)
{
	if (_mapActionInstaces.Contains(actionName))
	{
		*outActionInstance = _mapActionInstaces[actionName];
		return true;
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

void UState::MakeActionInstances() 
{
	for (auto actionClass : _arrayActionClasses)
	{
		if (_mapActionInstaces.Contains(actionClass.GetDefaultObject()->GetActionName()) == false)
		{
			static UAction* action = NewObject<UAction>(actionClass);
		
			if (action == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Make instance of UAction Failed!"));
				continue;
			}

			_mapActionInstaces.Add(action->GetActionName(), action);
		}
	}
}

EMovementMode UState::GetMovementMode() 
{
	return _movementMode;
}