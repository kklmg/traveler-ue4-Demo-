// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/OptionBase.h"
#include "Math/UnrealMathUtility.h"


void UOptionBase::Scroll(int32 delta)
{
	_curID = (_curID + delta) % VGetSize();

	if (_curID < 0)
	{
		_curID = VGetSize() + _curID;
	}
}

FORCEINLINE int32 UOptionBase::GetCurID()
{
	return _curID;
}


int32 UIntOption::VGetSize()
{
	return _options.Num();
}

int32 UIntOption::GetSelection()
{
	if (_options.Num() == 0) return 0;

	int32 curId = FMath::Clamp(GetCurID(), 0, _options.Num() - 1);
	return _options[curId];
}


int32 UFloatOption::VGetSize()
{
	return _options.Num();
}

float UFloatOption::GetSelection()
{
	if (_options.Num() == 0) return 0.0f;

	int32 curId = FMath::Clamp(GetCurID(), 0, _options.Num() - 1);
	return _options[curId];
}
