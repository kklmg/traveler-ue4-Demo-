// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActorWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ExTransformProviderComponent.h"

UActorWidget::UActorWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_timeCollapse = 5.0f;
}

void UActorWidget::SetData(AActor* widgetOwner, ETransform transformType)
{
	check(widgetOwner);
	_widgetOwner = widgetOwner;
	_transformType = transformType;

	_exTransformProviderComp = Cast<UExTransformProviderComponent>(_widgetOwner->GetComponentByClass(UExTransformProviderComponent::StaticClass()));
	OnWidgetOwnerChangedDelegate.Broadcast(_widgetOwner);
}

void UActorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!_widgetOwner) return;

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!controller) return;

	//Get Drawing Transform
	FTransform drawingTransform;
	if(_exTransformProviderComp
		&& _exTransformProviderComp->TryGetTransform(_transformType,ERelativeTransformSpace::RTS_World,drawingTransform))
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
		_elapsedTime_LeaveScreen = 0;
		float scale = UWidgetLayoutLibrary::GetViewportScale(this);
		screenPosition /= scale;

		SetVisibility(ESlateVisibility::Visible);
		SetRenderTranslation(screenPosition);
	}
	else
	{
		_elapsedTime_LeaveScreen += InDeltaTime;;
		if (_elapsedTime_LeaveScreen > _timeCollapse)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	
}

AActor* UActorWidget::GetWidgetOwner()
{
	return _widgetOwner;
}
