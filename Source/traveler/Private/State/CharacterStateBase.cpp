// Fill out your copyright notice in the Description page of Project Settings.


#include "State/CharacterStateBase.h"
#include "Components/ActionComponent.h"


void UCharacterStateBase::Initialize()
{
	if(ActionIdleClass!=nullptr)
	_actionIdle = NewObject<UAction>(this,ActionIdleClass);
	if (ActionMoveClass != nullptr)
	_actionMove = NewObject<UAction>(this, ActionMoveClass);
	if (ActionSprintClass != nullptr)
	_actionSprint = NewObject<UAction>(this, ActionSprintClass);
	if (ActionJumpClass != nullptr)
	_actionJump = NewObject<UAction>(this, ActionJumpClass);
	if (ActionTargetClass != nullptr)
	_actionTarget = NewObject<UAction>(this, ActionTargetClass);
	if (ActionDashClass != nullptr)
	_actionDash = NewObject<UAction>(this, ActionDashClass);
}


void UCharacterStateBase::Idle(UActionComponent* actionComponent)
{
	if (_actionIdle != nullptr)
	{
		_actionIdle->Start(actionComponent);
	}
}
void UCharacterStateBase::Move(UActionComponent* actionComponent)
{
	if (_actionMove != nullptr) 
	{
		_actionMove->Start(actionComponent);
	}
}
void UCharacterStateBase::Sprint(UActionComponent* actionComponent)
{
	if (_actionSprint != nullptr)
	{
		_actionSprint->Start(actionComponent);
	}
}
void UCharacterStateBase::Jump(UActionComponent* actionComponent)
{
	if (_actionJump != nullptr)
	{
		_actionJump->Start(actionComponent);
	}
}
void UCharacterStateBase::Target(UActionComponent* actionComponent)
{
	if (_actionTarget != nullptr)
	{
		_actionTarget->Start(actionComponent);
	}
}
void UCharacterStateBase::Dash(UActionComponent* actionComponent)
{
	if (_actionDash != nullptr)
	{
		_actionDash->Start(actionComponent);
	}
}


void UCharacterStateBase::Enter() 
{

}
void UCharacterStateBase::Leave()
{

}