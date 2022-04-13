// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EEffectType : uint8
{
	EEffectType_None UMETA(DisplayName = "None"),
	EEffectType_StatusEffect UMETA(DisplayName = "StatusEffect"),
	EEffectType_Dissolve UMETA(DisplayName = "Dissolve"),
};