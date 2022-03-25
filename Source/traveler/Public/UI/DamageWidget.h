// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Damage/MyDamageType.h"
#include "DamageWidget.generated.h"

USTRUCT(BlueprintType)
struct FDamageWidgetData
{
	GENERATED_USTRUCT_BODY()
public:
	FDamageWidgetData();

	FDamageWidgetData(FColor color);

	UPROPERTY(BlueprintReadOnly)
	float Damage;

	UPROPERTY(BlueprintReadOnly)
	FVector TextLocation;

	UPROPERTY(BlueprintReadOnly)
	FVector2D TextOffset;

	UPROPERTY(BlueprintReadOnly)
	float TextScale;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	FColor TextColor;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float ScrollSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FVector2D ScrollDirection;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float Life;
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetData(FDamageWidgetData damageWidgetData);

	bool IsLifeOver();
	
public:
	UPROPERTY(BlueprintReadOnly)
	FDamageWidgetData DamageWidgetData;

	UPROPERTY(BlueprintReadOnly)
	float ElapsedTime;

	UPROPERTY()
	FVector2D ScrollOffset;
};
