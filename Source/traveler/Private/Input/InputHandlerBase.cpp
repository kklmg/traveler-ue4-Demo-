// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandlerBase.h"
#include "Input/ButtonInputBase.h"


void UInputHandlerBase::Initialize()
{
	for (TSubclassOf<UButtonInputBase> buttonClass : _buttonClasses)
	{
		UButtonInputBase* buttonInput = NewObject<UButtonInputBase>(this);
		if(buttonInput)
		{
			_mapButtons.Add(buttonInput->GetInputType(), buttonInput);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Instatiate buttonInput failed"));
		}

	}
	
}

void UInputHandlerBase::HandleButtonPress(EInputType inputType)
{
	if (_mapButtons.Contains(inputType))
	{
		_mapButtons[inputType]->Press();
	}
}

void UInputHandlerBase::HandleButtonRelease(EInputType inputType)
{
	if (_mapButtons.Contains(inputType))
	{
		_mapButtons[inputType]->Release();
	}
}
