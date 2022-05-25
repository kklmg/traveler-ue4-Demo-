// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActorWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ExTransformProviderComponent.h"
#include "DrawDebugHelpers.h"

UActorWidget::UActorWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_timeCollapse = 5.0f;
	_distVisible = 10000.0f;
	_renderScaleMax = 1.4f;
	_renderScaleMin = 0.2f;
}

void UActorWidget::SetData(AActor* widgetOwner, ETransformType transformType)
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
	FTransform destTransform;
	if(_exTransformProviderComp
		&& _exTransformProviderComp->TryGetTransform(_transformType,ERelativeTransformSpace::RTS_World,destTransform))
	{
	}
	else
	{
		destTransform = _widgetOwner->GetActorTransform();
	}
	
	FVector2D viewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(viewportSize);

	FVector2D screenPosition;
	float renderScale = _renderScaleMax;
	bool isOnScreen = UGameplayStatics::ProjectWorldToScreen(controller, destTransform.GetLocation(), screenPosition);
	if (isOnScreen)
	{
		if (GetWorld()->GetFirstPlayerController())
		{
			APlayerCameraManager* cameraMng = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
			if (cameraMng)
			{
				_distFromCamera = FVector::Dist(destTransform.GetLocation(), cameraMng->GetCameraLocation());

				float normalizedDistFromCamera = FMath::Clamp(_distFromCamera / _distVisible, 0.0f, 1.0f);
				renderScale = FMath::Lerp(_renderScaleMin, _renderScaleMax, 1.0f - normalizedDistFromCamera);

				//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("_distFromCamera: %f"), _distFromCamera));
				//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("_distVisible: %f"), _distVisible));
				//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("normalize dist from camera: %f"), normalizedDistFromCamera));
				//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("renderScale: %f"), renderScale));
			}
		}

		float viewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
		screenPosition /= viewportScale;
		SetRenderTranslation(screenPosition);
		SetRenderScale(FVector2D(renderScale,renderScale));


		_elapsedTime_LeaveScreen = 0;
		SetVisibility(ESlateVisibility::Visible);
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
