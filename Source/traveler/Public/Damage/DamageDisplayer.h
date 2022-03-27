// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/CombatData.h"
#include "UI/DamageWidget.h"
#include "DamageDisplayer.generated.h"

class UObjectPoolBase;

USTRUCT(BlueprintType)
struct FDamageDisplayData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	EDamageType DamageType;

	UPROPERTY(BlueprintReadWrite)
	float Damage;

	UPROPERTY(BlueprintReadWrite)
	FVector Location;
};



/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UDamageDisplayer : public UObject
{
	GENERATED_BODY()
public:
	UDamageDisplayer();
	
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void ShowDamage(FDamageDisplayData damageDisplayData);

	void Tick(float DeltaTime);

private:
	void GetDamageWidgetData(FDamageDisplayData damageDisplayData, FVector2D offset, FDamageWidgetData& outDamageWidgetData);

	UPROPERTY(EditDefaultsOnly)
	TMap<EDamageType, FDamageWidgetData> _damageDisplaySetting;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageWidget> _damageWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	float _spawnInCircleRadius;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _textScaleCurve;

	UPROPERTY()
	UObjectPoolBase* _widgetPool;

	UPROPERTY(EditDefaultsOnly)
	int32 _poolSize;
};
