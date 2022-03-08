// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/MyDamageType.h"

UMyDamageType::UMyDamageType()
{
	bIsContinuousDamage = false;
	DamageType = EElementalDamageType::EEDT_Physics;
	DamageHandleInterval = 0.0f;
	DamageHandleCount = 1;
}

FName UMyDamageType::GetDamageTypeName()
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EElementalDamageType"), true);

	return enumPtr ? FName(enumPtr->GetNameStringByIndex((int32)DamageType)) : FName(TEXT("UnKnown"));
}
