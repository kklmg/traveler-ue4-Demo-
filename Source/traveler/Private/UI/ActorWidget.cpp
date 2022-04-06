// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActorWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Interface/ExtraTransformProvider.h"

void UActorWidget::SetData(AActor* widgetOwner, ETransform transformType)
{
	_widgetOwner = widgetOwner;
	_transformType = transformType;

	_ExTransformProviderInterface = Cast<IExtraTransformProvider>(_widgetOwner);

	OnWidgetOwnerChangedDelegate.Broadcast(_widgetOwner);
}

void UActorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!_widgetOwner) return;

	UWorld* world = GetWorld();
	if (!world) return;

	APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
	if (!controller) return;

	//Get Drawing Transform
	FTransform drawingTransform;
	if(_ExTransformProviderInterface
		&& _ExTransformProviderInterface->VTryGetTransform(_transformType,ERelativeTransformSpace::RTS_World,drawingTransform))
	{
	}
	else
	{
		drawingTransform = _widgetOwner->GetActorTransform();
	}
	
	//
	FVector2D screenPosition;
	bool isOnScreen = UGameplayStatics::ProjectWorldToScreen(controller, drawingTransform.GetLocation(), screenPosition);

	if (isOnScreen)
	{
		float scale = UWidgetLayoutLibrary::GetViewportScale(this);
		screenPosition /= scale;

		SetVisibility(ESlateVisibility::Visible);
		SetRenderTranslation(screenPosition);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
	
}

AActor* UActorWidget::GetWidgetOwner()
{
	return _widgetOwner;
}
