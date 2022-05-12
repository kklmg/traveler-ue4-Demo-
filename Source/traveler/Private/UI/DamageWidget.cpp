// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

FDamageWidgetData::FDamageWidgetData()
{
	TextScale = 1.0f;
	ScrollSpeed = 20.0f;
	ScrollDirection = FVector2D(0.0f, -1.0f);
	Life = 5.0f;
	ZOrder = 100;
};

FDamageWidgetData::FDamageWidgetData(FColor color)
{
	TextColor = color;

	TextScale = 1.0f;
	ScrollSpeed = 20.0f;
	ScrollDirection = FVector2D(0.0f, -1.0f);
	Life = 5.0f;
	ZOrder = 100;
}

void UDamageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (!_bIsActive) return;

	ElapsedTime += InDeltaTime;

	UWorld* world = GetWorld();
	if (!world) return;

	APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
	if (!controller) return;

	//world location to screen location
	FVector2D renderLocation;
	bool isOnScreen = UGameplayStatics::ProjectWorldToScreen(controller, DamageWidgetData.TextLocation, renderLocation);

	float scale = UWidgetLayoutLibrary::GetViewportScale(this);
	renderLocation /= scale;

	ScrollOffset += DamageWidgetData.ScrollDirection * DamageWidgetData.ScrollSpeed * InDeltaTime;

	SetRenderTranslation(renderLocation + ScrollOffset);

	if (ElapsedTime > DamageWidgetData.Life)
	{
		VInActivate();
	}
}


void UDamageWidget::SetData(FDamageWidgetData& damageWidgetData)
{
	DamageWidgetData = damageWidgetData;
	ScrollOffset = damageWidgetData.TextOffset;

	OnDataUpdated.Broadcast();
}


bool UDamageWidget::VIsActive()
{
	return _bIsActive;
}

bool UDamageWidget::VActivate()
{
	if (!_bIsActive)
	{
		_bIsActive = true;
		AddToViewport(DamageWidgetData.ZOrder);
		return true;
	}
	else
	{
		return false;
	}
}

bool UDamageWidget::VInActivate()
{
	if (_bIsActive)
	{
		_bIsActive = false;
		RemoveFromViewport();
		_onObjectInActive.ExecuteIfBound(_poolId);

		ElapsedTime = 0.0f;

		if(_bMarkDestroy)
		{
			MarkPendingKill();
		}

		return true;
	}
	else
	{
		return false;
	}
}

void UDamageWidget::VMarkDestroy()
{
	_bMarkDestroy = true;

	if (_bIsActive == false)
	{
		MarkPendingKill();
	}
}

int UDamageWidget::VGetPoolId()
{
	return _poolId;
}

void UDamageWidget::VSetPoolId(int32 poolId)
{
	_poolId = poolId;
}

FOnObjectInactive* UDamageWidget::VGetObjectInactiveDelegate()
{
	return &_onObjectInActive;
}

