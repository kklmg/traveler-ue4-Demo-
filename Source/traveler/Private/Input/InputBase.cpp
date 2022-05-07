// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputBase.h"

UInputBase::UInputBase()
{
}

void UInputBase::Init(UInputPresetBase* inputPreset)
{
	_inputPrest = inputPreset;
}

void UInputBase::SetBindingName(FName bindingName)
{
	_bindingName = bindingName;
}

FORCEINLINE_DEBUGGABLE FName UInputBase::GetBindingName()
{
	return _bindingName;
}

FORCEINLINE_DEBUGGABLE UInputPresetBase* UInputBase::GetInputPreset()
{
	check(_inputPrest);
	return _inputPrest;
}

