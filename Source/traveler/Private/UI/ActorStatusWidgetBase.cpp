// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActorStatusWidgetBase.h"
#include "Process/CompositeProcessBase.h"
#include "Components/PanelWidget.h"
#include "Blueprint/WidgetTree.h"

void UActorStatusWidgetBase::ShowStatus(EStatusEffect statusEffectType, float duration)
{
	if (_widgetInsMap.Contains(statusEffectType))
	{
		_widgetInsMap[statusEffectType]->Reset();
		_widgetInsMap[statusEffectType]->SetOpacityCurve(_opacityCurve);
		_widgetInsMap[statusEffectType]->SetDuration(duration);
		_widgetInsMap[statusEffectType]->SetTimeLineData(_flickeringTimeLineData);
		_widgetInsMap[statusEffectType]->SetVisibility(ESlateVisibility::Visible);
		_widgetInsMap[statusEffectType]->ExecuteFlickeringProcess();
	}
}

void UActorStatusWidgetBase::HideStatus(EStatusEffect statusEffectType)
{
	if (_widgetInsMap.Contains(statusEffectType))
	{
		_widgetInsMap[statusEffectType]->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UActorStatusWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Fire, statusFire);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Water, statusWater);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Ice, statusIce);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Electricity, statusElectricity);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Poison, statusPoison);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Stun, statusStun);
}

void UActorStatusWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
