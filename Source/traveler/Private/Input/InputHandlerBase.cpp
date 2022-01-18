// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandlerBase.h"
#include "Input/ButtonInputBase.h"
#include "Input/AxisInputBase.h"


void UInputHandlerBase::Initialize()
{
	//instantiate axis inputs
	for (TSubclassOf<UAxisInputBase> axisClass : _axisClasses)
	{
		UAxisInputBase* axisInput = NewObject<UAxisInputBase>(this, axisClass);
		if (axisInput)
		{
			_mapAxis.Add(axisInput->GetInputType(), axisInput);
		}
		else
		{
			UE_LOG(LogTemp, Fatal, TEXT("Instatiate axisInput failed"));
		}
	}

	//instantiate button inputs
	for (TSubclassOf<UButtonInputBase> buttonClass : _buttonClasses)
	{
		UButtonInputBase* buttonInput = NewObject<UButtonInputBase>(this);
		if(buttonInput)
		{
			_mapButtons.Add(buttonInput->GetActionName(), buttonInput);
		}
		else
		{
			UE_LOG(LogTemp, Fatal,TEXT("Instatiate buttonInput failed"));
		}
	}
}

void UInputHandlerBase::HandleAxisInput(EInputType inputType, float value)
{
	if (_mapAxis.Contains(inputType))
	{
		_mapAxis[inputType]->VHandleInput(value);
	}
}

void UInputHandlerBase::HandleButtonPress(FName actionName)
{
	if (_mapButtons.Contains(actionName))
	{
		_mapButtons[actionName]->VPress();
	}
}

void UInputHandlerBase::HandleButtonRelease(FName actionName)
{
	if (_mapButtons.Contains(actionName))
	{
		_mapButtons[actionName]->VRelease();
	}
}