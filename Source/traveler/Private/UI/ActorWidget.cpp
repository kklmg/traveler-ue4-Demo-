// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActorWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ExTransformProviderComponent.h"
#include "DrawDebugHelpers.h"

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
	
	FVector2D viewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(viewportSize);

	//
	FVector2D screenPosition;
	bool isOnScreen = UGameplayStatics::ProjectWorldToScreen(controller, drawingTransform.GetLocation(), screenPosition);
	if (isOnScreen)
	{
		//float tests = 1.0f;
		//if (GetWorld()->GetFirstPlayerController())
		//{
		//	APlayerCameraManager* cameraMng = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		//	if (cameraMng)
		//	{
		//		auto what = cameraMng->GetCameraCachePOV();
		//		what.OrthoFarClipPlane;

		//		//float dis = (drawingTransform.GetLocation() - cameraMng->GetCameraLocation()).Size();
		//		//tests = dis / 2048;
		//		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("viewportScale : %f"), sss));
		//		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("dis : %f"), dis));
		//		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("what.OrthoFarClipPlane; : %f"), what.OrthoFarClipPlane));
		//	}
		//}


		_elapsedTime_LeaveScreen = 0;
		float scale = UWidgetLayoutLibrary::GetViewportScale(this);
		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Screen position" + screenPosition.ToString());
		screenPosition /= scale;
		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("viewportScale 2: %f"), scale));
		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Screen position / Scale " + screenPosition.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, "viewport size" + viewportSize.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, RenderTransformPivot.ToString());

		SetVisibility(ESlateVisibility::Visible);

		
		SetRenderTranslation(screenPosition);

		RenderTransformPivot = FVector2D::ZeroVector;
		//setrenderi
		SetRenderScale(FVector2D(0.5f, 0.5f));
		//SetRenderScale();
	}
	else
	{
		_elapsedTime_LeaveScreen += InDeltaTime;;
		if (_elapsedTime_LeaveScreen > _timeCollapse)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	DrawDebugSphere(GetWorld(), drawingTransform.GetLocation(),5,2,FColor::Black);




	//
	//FVector2D Resolution = FVector2D(GSystemResolution.ResX, GSystemResolution.ResY);


	FVector Ground(drawingTransform.GetLocation());
	Ground.Z = 0;
	DrawDebugLine(GetWorld(), drawingTransform.GetLocation(), Ground, FColor::Black,false,-1.0f,0U,5.0f);
}

AActor* UActorWidget::GetWidgetOwner()
{
	return _widgetOwner;
}
