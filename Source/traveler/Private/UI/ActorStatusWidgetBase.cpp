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
		_widgetInsMap[statusEffectType]->SetDuration(duration);
		_widgetInsMap[statusEffectType]->SetVisibility(ESlateVisibility::Visible);
		_widgetInsMap[statusEffectType]->ExecuteFlickeringProcess();
	}
}

void UActorStatusWidgetBase::HideStatus(EStatusEffect statusEffectType)
{
	if (_widgetInsMap.Contains(statusEffectType))
	{
		_widgetInsMap[statusEffectType]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UActorStatusWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	statusFire->SetData(_flickeringWidgetData);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Fire, statusFire);

	statusWater->SetData(_flickeringWidgetData);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Water, statusWater);

	statusIce->SetData(_flickeringWidgetData);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Ice, statusIce);

	statusElectricity->SetData(_flickeringWidgetData);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Electricity, statusElectricity);

	statusPoison->SetData(_flickeringWidgetData);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Poison, statusPoison);

	statusStun->SetData(_flickeringWidgetData);
	_widgetInsMap.Add(EStatusEffect::EStatusEffect_Stun, statusStun);
}

void UActorStatusWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
