// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ButtonInputWithDelegate.h"

UButtonInputWithDelegate::UButtonInputWithDelegate()
{

}

void UButtonInputWithDelegate::VTMPress()
{
	OnButtonPressed.ExecuteIfBound(this);
}

void UButtonInputWithDelegate::VTMPressing(float deltaTime)
{
	OnButtonPressing.ExecuteIfBound(this);
}

void UButtonInputWithDelegate::VTMRelease()
{
	OnButtonReleased.ExecuteIfBound(this);
}
