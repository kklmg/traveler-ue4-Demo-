// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BillBoardWidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/BillBoardWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"


UBillBoardWidgetComponent::UBillBoardWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	_widgetOffset.Set(0, 0, 120);
}

void UBillBoardWidgetComponent::InitializeComponent()
{

}

void UBillBoardWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (_widgetClass != nullptr)
	{
		_widget = NewObject<UUserWidget>(this, _widgetClass);
		_widget->AddToViewport(100);

		//_widget->getoute

		_updateWidgetLocation();
	}

}

void UBillBoardWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_updateWidgetLocation();
}

void UBillBoardWidgetComponent::_updateWidgetLocation()
{
	if (!_widget) return;

	UWorld* world = GetWorld();
	if (!world) return;

	APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
	if (!controller) return;

	AActor* owner = GetOwner();
	if (!owner) return;


	FVector2D screenPosition;
	bool isOnScreen = UGameplayStatics::ProjectWorldToScreen(controller,owner->GetActorLocation() + _widgetOffset, screenPosition);

	if (isOnScreen)
	{
		float scale = UWidgetLayoutLibrary::GetViewportScale(_widget);
		screenPosition /= scale;


		_widget->SetVisibility(ESlateVisibility::Visible);
		_widget->SetRenderTranslation(screenPosition);
	}
	else
	{
		_widget->SetVisibility(ESlateVisibility::Hidden);
	}

	
}
