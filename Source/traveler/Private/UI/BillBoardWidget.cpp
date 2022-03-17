// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BillBoardWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UBillBoardWidget* UBillBoardWidget::MakeInstance(UObject* outer, TSubclassOf<UBillBoardWidget> widgetClass, AActor* owner,FVector widgetOffset)
{
	UBillBoardWidget* newWidget = nullptr;
    newWidget = NewObject<UBillBoardWidget>(outer, widgetClass);
	if(newWidget)
	{
		newWidget->SetData(owner,widgetOffset);
	}
	return newWidget;
}

UBillBoardWidget* UBillBoardWidget::MakeInstance(UObject* outer, AActor* owner, FActorUIData widgetData)
{
	UBillBoardWidget* newWidget = nullptr;
	newWidget = NewObject<UBillBoardWidget>(outer, widgetData.WidgetClass);
	if (newWidget)
	{
		newWidget->SetData(owner, widgetData.WidgetOffset);
	}
	return newWidget;
}

void UBillBoardWidget::SetData(AActor* widgetOwner, FVector widgetOffset)
{
	_widgetOwner = widgetOwner;
	_widgetOffset = widgetOffset;
}

void UBillBoardWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	UWorld* world = GetWorld();
	if (!world) return;

	APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
	if (!controller) return;

	if(world && controller && _widgetOwner)
	{	
		FVector2D screenPosition;
		bool isOnScreen = UGameplayStatics::ProjectWorldToScreen(controller, _widgetOwner->GetActorLocation() + _widgetOffset, screenPosition);

		if (isOnScreen)
		{
			float scale = UWidgetLayoutLibrary::GetViewportScale(this);
			screenPosition /= scale;

			SetVisibility(ESlateVisibility::Visible);
			SetRenderTranslation(screenPosition);
		}
		else
		{
			SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

AActor* UBillBoardWidget::GetWidgetOwner()
{
	return _widgetOwner;
}
