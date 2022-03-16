// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActorStatusWidgetBase.h"
#include "Process/CompositeProcessBase.h"
#include "UI/FlickeringWidget.h"
#include "Components/PanelWidget.h"
#include "Blueprint/WidgetTree.h"

void UActorStatusWidgetBase::ShowStatus(EActorStatusUI actorStatus, float duration)
{
	if (_widgetInsMap.Contains(actorStatus))
	{
		//_widgetInsMap[actorStatus]->set
	}
	else if(_widgetClassMap.Contains(actorStatus))
	{
		UFlickeringWidget* newStatus = WidgetTree->ConstructWidget<UFlickeringWidget>(_widgetClassMap[actorStatus]);

		statusHolder->AddChild(newStatus);
		_widgetInsMap.Add(actorStatus,newStatus);
	}
}

void UActorStatusWidgetBase::HideStatus(EActorStatusUI actorStatus, float duration)
{
	if (_widgetInsMap.Contains(actorStatus))
	{
		_widgetInsMap[actorStatus]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UActorStatusWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	//test code
	ShowStatus(EActorStatusUI::EAStatus_Fire, 20);
}

void UActorStatusWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
