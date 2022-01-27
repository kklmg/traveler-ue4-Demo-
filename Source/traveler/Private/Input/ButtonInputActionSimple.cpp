// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputActionSimple.h"

void UButtonInputActionSimple::VTMPress()
{
	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(_actionType);
	}
}