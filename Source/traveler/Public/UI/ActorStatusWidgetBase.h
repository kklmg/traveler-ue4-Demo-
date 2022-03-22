// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Process/CompositeProcessBase.h"
#include "UI/FlickeringWidget.h"
#include "Data/ActorUIData.h"
#include "UI/BillBoardWidget.h"
#include "ActorStatusWidgetBase.generated.h"


class UPanelWidget;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActorStatusWidgetBase : public UBillBoardWidget
{
	GENERATED_BODY()
	
public:
	void ShowStatus(EActorStatusUI actorStatus, float duration);
	void HideStatus(EActorStatusUI actorStatus);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	UPROPERTY(EditAnyWhere, meta = (bindwidget))
	UFlickeringWidget* statusFire;

	UPROPERTY(EditAnyWhere, meta = (bindwidget))
	UFlickeringWidget* statusWater;

	UPROPERTY(EditAnyWhere, meta = (bindwidget))
	UFlickeringWidget* statusIce;

	UPROPERTY(EditAnyWhere, meta = (bindwidget))
	UFlickeringWidget* statusElectricity;

	UPROPERTY(EditAnyWhere, meta = (bindwidget))
	UFlickeringWidget* statusPoison;

	UPROPERTY(EditAnyWhere, meta = (bindwidget))
	UFlickeringWidget* statusStun;

	UPROPERTY(EditAnywhere)
	UCurveFloat* _opacityCurve;

	UPROPERTY(EditAnywhere)
	TArray<FTimeFrameFlickeringData> _flickeringTimeLineData;

	UPROPERTY()
	TMap<EActorStatusUI, UFlickeringWidget*> _widgetInsMap; 
};


