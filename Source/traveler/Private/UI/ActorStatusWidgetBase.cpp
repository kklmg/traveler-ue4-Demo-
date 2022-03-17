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
		_widgetInsMap[actorStatus]->SetDuration(duration);
	}
	else if(_widgetClassMap.Contains(actorStatus))
	{
		UFlickeringWidget* newStatus = WidgetTree->ConstructWidget<UFlickeringWidget>(_widgetClassMap[actorStatus]);
		newStatus->SetOpacityCurve(_opacityCurve);
		newStatus->SetDuration(duration);
		newStatus->SetTimeLineData(_flickeringTimeLineData);

		newStatus->ExecuteFlickeringProcess();

		statusHolder->AddChild(newStatus);
		_widgetInsMap.Add(actorStatus,newStatus);
	}
}

void UActorStatusWidgetBase::HideStatus(EActorStatusUI actorStatus, float duration)
{
	if (_widgetInsMap.Contains(actorStatus))
	{
		_widgetInsMap[actorStatus]->RemoveFromParent();
		_widgetInsMap.Remove(actorStatus);
	}
}

void UActorStatusWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UActorStatusWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
