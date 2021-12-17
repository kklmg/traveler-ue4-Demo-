// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BillBoardWidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"


UBillBoardWidgetComponent::UBillBoardWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBillBoardWidgetComponent::InitializeComponent()
{

}

void UBillBoardWidgetComponent::BeginPlay()
{
	Super::BeginPlay();


	showWidget(EWidgetType::WT_HealthBar);

}

void UBillBoardWidgetComponent::showWidget(EWidgetType widgeType)
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

void UBillBoardWidgetComponent::HideWidget(EWidgetType widgeType)
{
	if (_mapWidgetInstance.Contains(widgeType))
	{
		_mapWidgetInstance[widgeType]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UBillBoardWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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
