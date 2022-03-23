// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/MyDamageType.h"

UMyDamageType::UMyDamageType()
{
	DamageType = EDamageType::EDamage_Physics;
}

FName UMyDamageType::GetDamageTypeName()
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDamageType"), true);

	return enumPtr ? FName(enumPtr->GetNameStringByIndex((int32)DamageType)) : FName(TEXT("UnKnown"));
}
