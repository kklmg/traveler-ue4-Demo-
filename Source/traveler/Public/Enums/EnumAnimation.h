// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAnimMontage : uint8
{
	EAnimMontage_None UMETA(DisplayName = "None"),
	EAnimMontage_Throw UMETA(DisplayName = "Throw"),
};