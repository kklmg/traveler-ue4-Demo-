// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStateBase.h"

void UCharacterStateBase::Move()
{
	if (_actionMove != nullptr) 
	{
		_actionMove->Start();
	}
}
void UCharacterStateBase::Sprint() 
{
	if (_actionSprint != nullptr)
	{
		_actionSprint->Start();
	}
}
void UCharacterStateBase::Jump()
{
	if (_actionJump != nullptr)
	{
		_actionJump->Start();
	}
}
void UCharacterStateBase::Target()
{
	if (_actionTarget != nullptr)
	{
		_actionTarget->Start();
	}
}
void UCharacterStateBase::Dash() 
{
	if (_actionDash != nullptr)
	{
		_actionDash->Start();
	}
}