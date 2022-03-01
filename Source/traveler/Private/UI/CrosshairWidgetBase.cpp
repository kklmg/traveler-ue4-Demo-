// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CrosshairWidgetBase.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "UI/AnimatedImageBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UCrosshairWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	_durationTime = 2.0f;
}


void UCrosshairWidgetBase::SetDurationTime(float durationTime)
{
	_durationTime = durationTime;
}

void UCrosshairWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TArray<UUserWidget*> foundedWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), foundedWidgets, UAnimatedImageBase::StaticClass(),false);


	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "widget count: " + FString::FromInt(foundedWidgets.Num()));

	for(UUserWidget* widgetElement : foundedWidgets)
	{
		UAnimatedImageBase* animImage = Cast<UAnimatedImageBase>(widgetElement);
		if(animImage)
		{
			AnimElements.Add(animImage);
		}
	}
}

void UCrosshairWidgetBase::Animate(float deltaTime, bool isForward)
{
	deltaTime = isForward ? deltaTime : -deltaTime;

	_elapsedTime = FMath::Clamp(_elapsedTime + deltaTime, 0.0f, _durationTime);
	float alpha = _elapsedTime / _durationTime;

	for(UAnimatedImageBase* animElement : AnimElements)
	{
		if (animElement)
		{
			animElement->Animate(alpha);
		}
	}
}

void UCrosshairWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}
