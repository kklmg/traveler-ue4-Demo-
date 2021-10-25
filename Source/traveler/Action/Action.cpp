// Fill out your copyright notice in the Description page of Project Settings.


#include"Action.h"


void UAction::Start() 
{
	if (_state == EActionState::AS_UNINITIALIZED)
	{
		VInitialize();
	}
}

void UAction::Pause()
{

}


void UAction::Stop() 
{
}

bool UAction::CanStart() 
{
	return _state != EActionState::AS_RUNNING;
}

FName UAction::GetActionName()
{
	return _actionName;
}


void UAction::VInitialize()
{

}
void UAction::VUpdate(unsigned long deltaMs)
{

}

EActionState UAction::GetState() const
{
	return _state;
}

void UAction::SetState(EActionState state)
{

}