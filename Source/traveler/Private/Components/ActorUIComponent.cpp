// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActorUIComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EventBrokerComponent.h"
#include "UI/ActorStatusWidgetBase.h"


UActorUIComponent::UActorUIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UActorUIComponent::InitializeComponent()
{
	Super::InitializeComponent();
	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));
}

void UActorUIComponent::BeginPlay()
{
	Super::BeginPlay();

	if (_eventBrokerComp)
	{
		_eventBrokerComp->SubscribeEvent(NSEventData::ActorLifeStateChanged::Name, this, &UActorUIComponent::OnReceiveEvent_LifeStateChanged);
	}
	
	if(_bShowStatusDefault)
	{
		ShowActorUI(EActorUI::ActorUI_Status);
	}
}

void UActorUIComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	RemoveAllUI();
}

void UActorUIComponent::ShowActorUI(EActorUI widgeType)
{
	if (_mapWidgetInstance.Contains(widgeType))
	{
		_mapWidgetInstance[widgeType]->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		if (_mapWidgetClass.Contains(widgeType))
		{
			UActorWidget* newWidget = NewObject<UActorWidget>(this, _mapWidgetClass[widgeType].WidgetClass);
			newWidget->SetData(GetOwner(), _mapWidgetClass[widgeType].TransformType);
			newWidget->AddToViewport(_mapWidgetClass[widgeType].ZOrder);
			newWidget->SetVisibility(ESlateVisibility::Visible);

			_mapWidgetInstance.Add(widgeType, newWidget);
		}
	}
}

void UActorUIComponent::HideActorUI(EActorUI widgeType)
{
	if (_mapWidgetInstance.Contains(widgeType))
	{
		_mapWidgetInstance[widgeType]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UActorUIComponent::HideAllUI()
{
	for (auto& element : _mapWidgetInstance)
	{
		if (element.Value)
		{
			element.Value->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UActorUIComponent::RemoveAllUI()
{
	for (auto& element : _mapWidgetInstance)
	{
		if (element.Value)
		{
			element.Value->RemoveFromViewport();
		}
	}
}

void UActorUIComponent::ShowActorStatusEffectUI(EStatusEffect StatusType, float duration)
{
	ShowActorUI(EActorUI::ActorUI_Status);

	if (_mapWidgetInstance.Contains(EActorUI::ActorUI_Status) == false) return;
	UActorStatusWidgetBase* statusUI = Cast<UActorStatusWidgetBase>(_mapWidgetInstance[EActorUI::ActorUI_Status]);

	if(statusUI)
	{
		statusUI->ShowStatus(StatusType, duration);
	}
}

void UActorUIComponent::HideActorStatusEffectUI(EStatusEffect StatusType)
{
	if (_mapWidgetInstance.Contains(EActorUI::ActorUI_Status) == false) return;
	UActorStatusWidgetBase* statusUI = Cast<UActorStatusWidgetBase>(_mapWidgetInstance[EActorUI::ActorUI_Status]);

	if (statusUI)
	{
		statusUI->HideStatus(StatusType);
	}
}

void UActorUIComponent::OnReceiveEvent_LifeStateChanged(UObject* baseData)
{
	auto eventData = Cast<NSEventData::ActorLifeStateChanged::Type>(baseData);
	if (eventData && eventData->Value == false)
	{
		RemoveAllUI();
	}	
}

void UActorUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto& element : _mapWidgetInstance)
	{
		check(element.Value)
		element.Value->Tick(DeltaTime);
	}
}

//void UBillBoardWidgetComponent::_updateWidgetLocation()
//{
//	if (!_widget) return;
//
//	UWorld* world = GetWorld();
//	if (!world) return;
//
//	APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
//	if (!controller) return;
//
//	AActor* owner = GetOwner();
//	if (!owner) return;
//
//
//	FVector2D screenPosition;
//	bool isOnScreen = UGameplayStatics::ProjectWorldToScreen(controller,owner->GetActorLocation() + _widgetOffset, screenPosition);
//
//	if (isOnScreen)
//	{
//		float scale = UWidgetLayoutLibrary::GetViewportScale(_widget);
//		screenPosition /= scale;
//
//
//		_widget->SetVisibility(ESlateVisibility::Visible);
//		_widget->SetRenderTranslation(screenPosition);
//	}
//	else
//	{
//		_widget->SetVisibility(ESlateVisibility::Hidden);
//	}
//
//	
//}
