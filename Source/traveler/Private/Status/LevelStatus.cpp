// Fill out your copyright notice in the Description page of Project Settings.


#include "Status/LevelStatus.h"


void ULevelStatus::SetLevel(int32 level, int32 exp)
{
	_level = level;
	_exp = exp;
}

int32 ULevelStatus::GetLevel()
{
	return _level;
}
