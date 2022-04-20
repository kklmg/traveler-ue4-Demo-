// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputActionBase.h"
#include "Components/ActionComponent.h"

void UButtonInputActionBase::Initialize(UActionComponent* actionComp)
{
	check(actionComp);
	_actionComp = actionComp;
}

EActionType UButtonInputActionBase::GetActionType()
{
	return _actionType;
}

FORCEINLINE_DEBUGGABLE UActionComponent* UButtonInputActionBase::GetActionComp()
{
	return _actionComp;
}
