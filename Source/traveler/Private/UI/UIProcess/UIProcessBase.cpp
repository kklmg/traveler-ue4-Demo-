// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIProcess/UIProcessBase.h"

void UUIProcessBase::SetWidget(UWidget* widget)
{
	_widget = widget;
}

UWidget* UUIProcessBase::GetWidget()
{
	return  _widget;
}