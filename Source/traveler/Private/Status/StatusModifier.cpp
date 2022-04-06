// Fill out your copyright notice in the Description page of Project Settings.


#include "Status/StatusModifier.h"
#include "Status/StatusBase.h"

void UStatusModifier::SetData(FName modifierName, EStatusType statusType, float value)
{
	_modiferName = modifierName;
    _statusType = statusType;
	_value = value;
}

float UStatusModifier::VGetDeltaValue(UStatusBase* statusBase)
{
    _value;
    return 0.0f;
}

FName UStatusModifier::GetModifierName()
{
    return _modiferName;
}

EStatusType UStatusModifier::GetStatusType()
{
    return _statusType;
}