// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputActionBase.h"

void UButtonInputActionBase::Initialize(IActionInterface* actionInterface)
{
	_actionInterface = actionInterface;
}

EActionType UButtonInputActionBase::GetActionType()
{
	return _actionType;
}
