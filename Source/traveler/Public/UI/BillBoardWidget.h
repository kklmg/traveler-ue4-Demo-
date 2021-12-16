// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BillBoardWidget.generated.h"


/**
 * 
 */
UCLASS()
class TRAVELER_API UBillBoardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Initialize(AActor* widgetOwner);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AActor* GetWidgetOwner();
private:
	UPROPERTY()
	AActor* _widgetOwner;
};
