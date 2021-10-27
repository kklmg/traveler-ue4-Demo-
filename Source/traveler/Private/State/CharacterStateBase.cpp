// Fill out your copyright notice in the Description page of Project Settings.


#include "State/CharacterStateBase.h"
#include "Components/ActionComponent.h"

void UCharacterStateBase::Move(UActionComponent* actionComponent)
{
	if (_actionMove != nullptr) 
	{
		_actionMove.GetDefaultObject()->Start(actionComponent);
	}
}
void UCharacterStateBase::Sprint(UActionComponent* actionComponent)
{
	if (_actionSprint != nullptr)
	{
		_actionSprint.GetDefaultObject()->Start(actionComponent);
	}
}
void UCharacterStateBase::Jump(UActionComponent* actionComponent)
{
	if (_actionJump != nullptr)
	{
		_actionJump.GetDefaultObject()->Start(actionComponent);
	}
}
void UCharacterStateBase::Target(UActionComponent* actionComponent)
{
	if (_actionTarget != nullptr)
	{
		_actionTarget.GetDefaultObject()->Start(actionComponent);
	}
}
void UCharacterStateBase::Dash(UActionComponent* actionComponent)
{
	if (_actionDash != nullptr)
	{
		_actionDash.GetDefaultObject()->Start(actionComponent);
	}
}


void UCharacterStateBase::Enter() 
{

}
void UCharacterStateBase::Leave()
{

}