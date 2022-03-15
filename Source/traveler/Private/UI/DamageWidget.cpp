// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

FDamageWidgetData::FDamageWidgetData()
{
	TextScale = FVector2D::UnitVector;
	ScrollSpeed = 20.0f;
	ScrollDirection = FVector2D(0.0f, -1.0f);
	Life = 5.0f;
}

void UDamageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) 
{
	if (IsLifeOver()) return;

	ElapsedTime += InDeltaTime;

	UWorld* world = GetWorld();
	if (!world) return;

	APlayerController* controller = UGameplayStatics::GetPlayerController(world, 0);
	if (!controller) return;

	//world location to screen location
	FVector2D renderLocation;
	bool isOnScreen = UGameplayStatics::ProjectWorldToScreen(controller, WorldLocation, renderLocation);

	float scale = UWidgetLayoutLibrary::GetViewportScale(this);
	renderLocation /= scale;

	ScrollOffset += DamageWidgetData.ScrollDirection * DamageWidgetData.ScrollSpeed * InDeltaTime;
	
	SetRenderTranslation(renderLocation + ScrollOffset);
}


void UDamageWidget::SetData(FVector worldLocation, float damageAmount, FDamageWidgetData damageWidgetData, FVector2D offset)
{
	WorldLocation = worldLocation,
	Damage = damageAmount;
	DamageWidgetData = damageWidgetData;
	ScrollOffset = offset;
}

bool UDamageWidget::IsLifeOver()
{
	return ElapsedTime > DamageWidgetData.Life;
}
