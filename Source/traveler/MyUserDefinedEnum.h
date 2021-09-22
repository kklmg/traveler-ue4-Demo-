// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "MyUserDefinedEnum.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UMyUserDefinedEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};


UENUM(BlueprintType)
enum class EEquipState : uint8
{
	ES_unEquiped UMETA(DisplayName = "unEquiped"),
	ES_bow UMETA(DisplayName = "bow")
};