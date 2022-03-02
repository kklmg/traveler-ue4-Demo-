// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CrosshairWidgetBase.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "UI/AnimatedImageBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


UCrosshairWidgetBase::UCrosshairWidgetBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_durationTime = 2.0f;
	_ZOrder = 100.0f;
}


void UCrosshairWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<UWidget*> foundedWidgets;
	if (WidgetTree)
	{
		WidgetTree->GetAllWidgets(foundedWidgets);

		for (UWidget* widgetElement : foundedWidgets)
		{
			UAnimatedImageBase* animImage = Cast<UAnimatedImageBase>(widgetElement);
			if (animImage)
			{
				animImage->Initialize();
				_animElements.Add(animImage);
			}
		}
	}
}


void UCrosshairWidgetBase::SetDurationTime(float durationTime)
{
	_durationTime = durationTime;
}

void UCrosshairWidgetBase::SetIsOnTarget(bool isOnTarget)
{
	_bIsOnTarget = isOnTarget;
}


void UCrosshairWidgetBase::Animate(float deltaTime)
{
	if (_widgetOnTarget)
	{
		_widgetOnTarget->SetVisibility(_bIsOnTarget && _elapsedTime >= _durationTime ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}


	if (_bIsAnimForward && _elapsedTime >= _durationTime)
	{
		return;
	}

	if (_bIsAnimForward == false && _elapsedTime <= 0.0f)
	{
		return;
	}

	if (_bIsAnimForward && IsInViewport() == false)
	{
		AddToViewport(_ZOrder);
	}


	deltaTime = _bIsAnimForward ? deltaTime : -deltaTime;
	_elapsedTime = FMath::Clamp(_elapsedTime + deltaTime, 0.0f, _durationTime);
	float alpha = _elapsedTime / _durationTime;

	for(UAnimatedImageBase* animElement : _animElements)
	{
		if (animElement)
		{
			animElement->Animate(alpha);
		}
	}

	if (_elapsedTime <= 0.0f && IsInViewport() && _bIsAnimForward == false)
	{
		RemoveFromViewport();
	}
}

void UCrosshairWidgetBase::SetAnimForward(bool isForward)
{
	_bIsAnimForward = isForward;
}

void UCrosshairWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}
