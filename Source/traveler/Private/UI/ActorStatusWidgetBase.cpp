// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActorStatusWidgetBase.h"
#include "Process/CompositeProcessBase.h"
#include "UI/FlickeringWidget.h"

void UActorStatusWidgetBase::ShowStatus(EActorStatusUI actorStatus, float duration)
{
	if (_widgetMap.Contains(actorStatus))
	{
		_widgetMap[actorStatus]->SetVisibility(ESlateVisibility::Visible);
	}
}

void UActorStatusWidgetBase::HideStatus(EActorStatusUI actorStatus, float duration)
{
	if (_widgetMap.Contains(actorStatus))
	{
		_widgetMap[actorStatus]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UActorStatusWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	_widgetMap.Add(EActorStatusUI::EAStatus_Fire, statusFire);
	_widgetMap.Add(EActorStatusUI::EAStatus_Water, statusWater);
	_widgetMap.Add(EActorStatusUI::EAStatus_Ice, statusIce);
	_widgetMap.Add(EActorStatusUI::EAStatus_Electricity, statusElectricity);
	_widgetMap.Add(EActorStatusUI::EAStatus_Poision, statusPoision);
	_widgetMap.Add(EActorStatusUI::EAStatus_Stun, statusStun);
}

void UActorStatusWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
