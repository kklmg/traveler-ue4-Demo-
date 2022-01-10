// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ThrowerData.h"

FThrowerData::FThrowerData()
{
	ThrowingRate = 0.5f;
	Speed = 500.0f;
	Scale = 1.0f;
	ConeAngle = 5.0f;
	ScaleCurve = nullptr;
	Life = 5.0f;
	Damage = 1.0f;
	Gravity = FVector(0, 0, 0);
}