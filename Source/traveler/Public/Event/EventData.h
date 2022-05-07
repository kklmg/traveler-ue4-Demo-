// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ObjectData.h"
#include "MyMacros.h"

/**
 * 
 */

namespace NSEvent
{
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(ActorDeathEffectFinished,UDataBool);
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(MovementModeChanged,UDataUInt8);
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(VelocityChanged,UDataVector);
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(ActorLifeStateChanged, UDataBool);
	DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(CharacterWantToSprint, UDataBool);
}

