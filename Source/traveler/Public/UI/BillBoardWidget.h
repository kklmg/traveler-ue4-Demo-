// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ActorUIData.h"
#include "BillBoardWidget.generated.h"




/**
 * 
 */
UCLASS()
class TRAVELER_API UBillBoardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	static UBillBoardWidget* MakeInstance(UObject* outer, AActor* owner,FActorUIData widgetData);
	static UBillBoardWidget* MakeInstance(UObject* outer,TSubclassOf<UBillBoardWidget> widgetClass,AActor* owner, FVector widgetOffset);

public:
	void SetData(AActor* widgetOwner,FVector widgetOffset);

	UFUNCTION(BlueprintCallable)
	AActor* GetWidgetOwner();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	AActor* _widgetOwner;

	UPROPERTY()
	FVector _widgetOffset;
};
