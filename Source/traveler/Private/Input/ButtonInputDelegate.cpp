// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputDelegate.h"

UButtonInputDelegate::UButtonInputDelegate()
{
}

void UButtonInputDelegate::VTMPress()
{
	OnButtonPressed.ExecuteIfBound(this);
}

void UButtonInputDelegate::VTMPressing(float deltaTime)
{
	OnButtonPressing.ExecuteIfBound(this);
}

void UButtonInputDelegate::VTMRelease()
{
	OnButtonReleased.ExecuteIfBound(this);
}
