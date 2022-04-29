// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/FlyingAbilityData.h"

FFlyingAbilityData::FFlyingAbilityData():
	YawAngSpeed(45.0f),
	PitchAngSpeed(5.0f),
	PitchLimit(80.0f),
	RollLimit(60.0f),
	SpeedXYMax(3200.0f),
	SpeedZMax(1000.0f),
	AccelXY(1000.0f),
	AccelZ(600.0f) {}
