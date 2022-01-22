// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputActionSimple.h"

void UButtonInputActionSimple::VPress()
{
	Super::VPress();

	if (_actionInterface)
	{
		_actionInterface->VExecuteAction(_actionType);
	}
}

//void UButtonInputActionSimple::VPressing(float deltaTime)
//{
//	Super::VPressing(deltaTime);
//}
//
//void UButtonInputActionSimple::VRelease()
//{
//	Super::VRelease();
//}
