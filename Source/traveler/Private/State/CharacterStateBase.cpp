// Fill out your copyright notice in the Description page of Project Settings.


#include "State/CharacterStateBase.h"
#include "Components/ActionComponent.h"



void UCharacterStateBase::Initialize(ACharacter* character)
{
	if (ActionIdleClass != nullptr)
	{
		_actionIdle = NewObject<UAction>(this, ActionIdleClass);
		_actionIdle->VInitialize(character);
	}
	if (ActionMoveClass != nullptr)
	{
		_actionMove = NewObject<UAction>(this, ActionMoveClass);
		_actionMove->VInitialize(character);
	}
	if (ActionSprintClass != nullptr)
	{
		_actionSprint = NewObject<UAction>(this, ActionSprintClass);
		_actionSprint->VInitialize(character);
	}
	if (ActionJumpClass != nullptr)
	{
		_actionJump = NewObject<UAction>(this, ActionJumpClass);
		_actionJump->VInitialize(character);
	}
	if (ActionTargetClass != nullptr)
	{
		_actionTarget = NewObject<UAction>(this, ActionTargetClass);
		_actionTarget->VInitialize(character);
	}
	if (ActionDashClass != nullptr)
	{
		_actionDash = NewObject<UAction>(this, ActionDashClass);
		_actionDash->VInitialize(character);
	}
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