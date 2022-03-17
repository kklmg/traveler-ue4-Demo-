// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "UI/BillBoardWidget.h"
#include "BillBoardWidgetComponent.generated.h"


class UUserWidget;
/**
 * 
 */
UCLASS()
class TRAVELER_API UBillBoardWidgetComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBillBoardWidgetComponent();
protected:

	virtual void InitializeComponent() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShowWidget(EActorUI widgeType);
	void HideWidget(EActorUI widgeType);

private:

	UPROPERTY(EditDefaultsOnly)
	TMap<EActorUI,FActorUIData> _mapWidgetClass;

	UPROPERTY()
	TMap<EActorUI, UBillBoardWidget*> _mapWidgetInstance;

	UPROPERTY()
	UBillBoardWidget* _widget;

};
