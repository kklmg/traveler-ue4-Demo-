// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputActionSimple.h"
#include "Components/ActionComponent.h"

void UButtonInputActionSimple::VTMPress()
{
	check(GetActionComp())
	GetActionComp()->ExecuteAction(_actionType);
}