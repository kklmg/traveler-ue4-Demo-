// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Process/CompositeProcessBase.h"
#include "UI/FlickeringWidget.h"
#include "Enums/EnumCombat.h"
#include "UI/ActorWidget.h"
#include "ActorStatusWidgetBase.generated.h"


class UPanelWidget;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActorStatusWidgetBase : public UActorWidget
{
	GENERATED_BODY()
	
public:
	void ShowStatus(EStatusEffect statusEffectType, float duration);
	void HideStatus(EStatusEffect statusEffectType);
	virtual bool Tick(float deltaTime) override;

protected:
	virtual void NativeConstruct() override;

	

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
	FFlickeringWidgetData _flickeringWidgetData;

	UPROPERTY()
	TMap<EStatusEffect, UFlickeringWidget*> _widgetInsMap; 
};


