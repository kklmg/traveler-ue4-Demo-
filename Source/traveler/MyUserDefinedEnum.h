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

UENUM(BlueprintType)
enum class EActionState : uint8
{
	AS_Jump UMETA(DisplayName = "Jump"),
	AS_Walk UMETA(DisplayName = "Walk"),
	AS_Run UMETA(DisplayName = "Run"),
	AS_Stop UMETA(DisplayName = "Stop"),
	AS_StartAim UMETA(DisplayName = "StartAim"),
	AS_Aiming UMETA(DisplayName = "Aiming"),
	AS_StopAim UMETA(DisplayName = "StopAim"),

};