// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/EnumTransformType.h"
#include "ActorUIData.generated.h"

class UActorWidget;

/**
 * 
 */
UENUM(BlueprintType)
enum class EActorUI : uint8
{
	ActorUI_None UMETA(DisplayName = "None"),
	//ActorUI_HealthBar UMETA(DisplayName = "HealthBar"),
	ActorUI_DamageInfo UMETA(DisplayName = "DamageInfo"),
	ActorUI_Status UMETA(DisplayName = "Status"),
};


USTRUCT(BlueprintType)
struct FActorUIData
{
	GENERATED_USTRUCT_BODY()
public:
	FActorUIData();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UActorWidget> WidgetClass;

	UPROPERTY(EditDefaultsOnly)
	ETransform TransformType;

	UPROPERTY(EditDefaultsOnly)
	float ZOrder;
};



//UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
//enum class EActorStatusUI
//{
//	EAStatus_NONE = 0 UMETA(Hidden),
//	EAStatus_Level = 1 << 0 UMETA(DisplayName = "Level"),
//	EAStatus_Health = 1 << 1 UMETA(DisplayName = "Health"),
//	EAStatus_Mana = 1 << 2 UMETA(DisplayName = "Mana"),
//	EAStatus_Stamina = 1 << 3 UMETA(DisplayName = "Stamina"),
//	EAStatus_Energy = 1 << 4 UMETA(DisplayName = "Energy"),
//	EAStatus_Fire = 1 << 5 UMETA(DisplayName = "Fire"),
//	EAStatus_Water = 1 << 6 UMETA(DisplayName = "Water"),
//	EAStatus_Ice = 1 << 7 UMETA(DisplayName = "Ice"),
//	EAStatus_Electricity = 1 << 8 UMETA(DisplayName = "Electricity"),
//	EAStatus_Poision = 1 << 9 UMETA(DisplayName = "Poision"),
//	EAStatus_Stun = 1 << 10 UMETA(DisplayName = "Stun"),
//};
//ENUM_CLASS_FLAGS(EActorStatusUI);