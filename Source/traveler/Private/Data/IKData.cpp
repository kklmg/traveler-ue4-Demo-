// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/IKData.h"

void UIKFootData::SetLeft(FIKData IKData)
{
	_leftData = IKData;
}

void UIKFootData::SetRight(FIKData IKData)
{
	_rightData = IKData;
}

FIKData UIKFootData::GetLeft()
{
	return _leftData;
}

FIKData UIKFootData::GetRight()
{
	return _rightData;
}
