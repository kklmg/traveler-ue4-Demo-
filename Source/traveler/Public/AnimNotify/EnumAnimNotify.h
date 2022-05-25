// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAnimNotifyKeyType : uint8
{
	ANK_SpreadAttack UMETA(DisplayName = "SpreadAttack"),
	ANK_MeleeAttack UMETA(DisplayName = "MeleeAttack"),
	ANK_SpitAttack UMETA(DisplayName = "SpitAttack"),
};

