// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputDelegate.h"

UButtonInputDelegate::UButtonInputDelegate()
{
}

void UButtonInputDelegate::VOnPressed()
{
	_onButtonPressed.ExecuteIfBound();
}

void UButtonInputDelegate::VOnPressing(float deltaTime)
{
	_onButtonPressing.ExecuteIfBound(deltaTime);
}

void UButtonInputDelegate::VOnReleased()
{
	_onButtonReleased.ExecuteIfBound();
}
