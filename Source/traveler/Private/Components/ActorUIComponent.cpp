// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActorUIComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ActorStatusWidgetBase.h"


UActorUIComponent::UActorUIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UActorUIComponent::InitializeComponent()
{

}

void UActorUIComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if(_bShowStatusDefault)
	{
		ShowActorUI(EActorUI::ActorUI_Status);
	}
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
			UBillBoardWidget* newWidget = UBillBoardWidget::MakeInstance(this, GetOwner(), _mapWidgetClass[widgeType]);
			newWidget->AddToViewport(100);
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

void UActorUIComponent::ShowActorStatusUI(EActorStatusUI StatusUIType, float duration)
{
	ShowActorUI(EActorUI::ActorUI_Status);

	if (_mapWidgetInstance.Contains(EActorUI::ActorUI_Status) == false) return;
	UActorStatusWidgetBase* statusUI = Cast<UActorStatusWidgetBase>(_mapWidgetInstance[EActorUI::ActorUI_Status]);

	if(statusUI)
	{
		statusUI->ShowStatus(StatusUIType, duration);
	}
}

void UActorUIComponent::HideActorStatusUI(EActorStatusUI StatusUIType)
{
	if (_mapWidgetInstance.Contains(EActorUI::ActorUI_Status) == false) return;
	UActorStatusWidgetBase* statusUI = Cast<UActorStatusWidgetBase>(_mapWidgetInstance[EActorUI::ActorUI_Status]);

	if (statusUI)
	{
		statusUI->HideStatus(StatusUIType);
	}
}

void UActorUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//_updateWidgetLocation();
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