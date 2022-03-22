// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActorStatusWidgetBase.h"
#include "Process/CompositeProcessBase.h"
#include "Components/PanelWidget.h"
#include "Blueprint/WidgetTree.h"

void UActorStatusWidgetBase::ShowStatus(EActorStatusUI actorStatus, float duration)
{
	if (_widgetInsMap.Contains(actorStatus))
	{
		_widgetInsMap[actorStatus]->Reset();
		_widgetInsMap[actorStatus]->SetOpacityCurve(_opacityCurve);
		_widgetInsMap[actorStatus]->SetDuration(duration);
		_widgetInsMap[actorStatus]->SetTimeLineData(_flickeringTimeLineData);
		_widgetInsMap[actorStatus]->SetVisibility(ESlateVisibility::Visible);
		_widgetInsMap[actorStatus]->ExecuteFlickeringProcess();
	}
}

void UActorStatusWidgetBase::HideStatus(EActorStatusUI actorStatus)
{
	if (_widgetInsMap.Contains(actorStatus))
	{
		_widgetInsMap[actorStatus]->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UActorStatusWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	_widgetInsMap.Add(EActorStatusUI::EAStatus_Fire, statusFire);
	_widgetInsMap.Add(EActorStatusUI::EAStatus_Water, statusWater);
	_widgetInsMap.Add(EActorStatusUI::EAStatus_Ice, statusIce);
	_widgetInsMap.Add(EActorStatusUI::EAStatus_Electricity, statusElectricity);
	_widgetInsMap.Add(EActorStatusUI::EAStatus_Poison, statusPoison);
	_widgetInsMap.Add(EActorStatusUI::EAStatus_Stun, statusStun);
}

void UActorStatusWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
