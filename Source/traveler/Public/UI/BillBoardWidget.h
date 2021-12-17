// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BillBoardWidget.generated.h"


UENUM(BlueprintType)
enum class EWidgetType: uint8
{
	WT_None UMETA(DisplayName = "None"),
	WT_HealthBar UMETA(DisplayName = "HealthBar"),
	WT_DamageInfo UMETA(DisplayName = "DamageInfo"),
};

USTRUCT(BlueprintType)
struct FWidgetData
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBillBoardWidget> WidgetClass;
	UPROPERTY(EditDefaultsOnly)
	FVector WidgetOffset;
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UBillBoardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	static UBillBoardWidget* MakeInstance(UObject* outer, AActor* owner,FWidgetData widgetData);
	static UBillBoardWidget* MakeInstance(UObject* outer,TSubclassOf<UBillBoardWidget> widgetClass,AActor* owner, FVector widgetOffset);

public:
	void SetData(AActor* widgetOwner,FVector widgetOffset);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AActor* GetWidgetOwner();
private:
	UPROPERTY()
	AActor* _widgetOwner;

	UPROPERTY()
	FVector _widgetOffset;
};
