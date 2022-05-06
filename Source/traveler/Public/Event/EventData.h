// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ObjectData.h"

/**
 * 
 */

#define MyEvent(EventName) namespace EventName{ const FName Name = FName(TEXT(#EventName));};
#define MyEventWithData(EventName, EventDataType)  namespace EventName{ const FName Name = FName(TEXT(#EventName)); typedef EventDataType DataType;};



namespace NSEvent
{
	MyEventWithData(ActorDeathEffectFinished,UDataBool);
	MyEventWithData(MovementModeChanged,UDataUInt8);
	MyEventWithData(VelocityChanged,UDataVector);
	MyEventWithData(ActorLifeStateChanged, UDataBool);
	MyEventWithData(CharacterWantToSprint, UDataBool);
}

